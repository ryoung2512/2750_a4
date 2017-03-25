#include "a1.h"

int main(int argc, char const *argv[]) {
    if (argc == 1)
    {
        printf("Error no arguements were entered.\n");
        exit(1);
    }
    FILE * file;
    file = fopen(argv[1], "r");
    checkFile(file, argv[1]);
    parseFile(file, argv[1]);
    fclose(file);
    return 0;
}

Node * addWord(Node * theList, char * word)
{
    if (strlen(word) != 0)
    {
        Node * newNode = createRecord(word);
        return addToBack(theList, newNode);
    }
    return theList;
}

void checkFile(FILE* file, const char * fileName)
{
    /* Checks if the file exists */
    if (file == NULL)
    {
        printf("Error: %s does not exist!\n", fileName);
        exit(1);
    }
}

void mainFunctions(Node * list, const char * fileName)
{
    if (list != NULL)
    {
        /*
            Order of Operations
            fixFunctionCalls(list);
            fixClassVariables(list);
            renameFunctions(list);
            finishFunctionCalls(list);
            createConstructors(list);
            fixBrackets(list);
            createConstructorCalls(list);
            fixFunctionPtrs(list);
        */

        /* Lets make sure there is no trickery */
        replaceRecord(list, "struct", "class");


        fixFunctionCalls(list);
        fixClassVariables(list);
        renameFunctions(list);
        finishFunctionCalls(list);
        createConstructors(list);
        fixBrackets(list);
        createConstructorCalls(list);
        fixFunctionPtrs(list);

        createFunctionPrototypes(list);

        replaceRecord(list, "class", "struct");

        /* Breaks up the filename to send it to the printlist Function */
        char tempFileName[50];
        strcpy(tempFileName, fileName);
        char * temp = strtok(tempFileName, ".");
        char fName[50];
        strcpy(fName, temp);
        strcat(fName, ".c");

        printList(list, fName);
        destroyList(list);
    }
    else
    {
        printf("Empty file nothing to do here, gg ez\n");
        exit(1);
    }
}

void parseFile(FILE * file, const char * fileName)
{
    Node * list = NULL;
    int count = 0, dontPrint = 0;
    char temp, last, flag, word[500];
    while((temp = getc(file)) != EOF)
    {   /* whitespace */
        if (temp == ' ' || temp == '\n' || temp == '\t' || temp == '\r')
        {
            word[count] = '\0';
            count = 0;
            list = addWord(list, word);
        } /* punctuation */
        else if (temp == ',' || temp == ';'|| temp == '(' || temp == ')' ||
         temp == '{'|| temp == '}' || temp == ',' || temp == '[' || temp == ']')
        {
            word[count] = '\0';
            count = 0;
            list = addWord(list, word);

            word[count++] = temp;
            word[count] = '\0';
            count = 0;
            list = addWord(list, word);
        }
        else
        {
            if ((temp == '"' || temp == '\'')) /* strings */
            {
                int escapeCount = 0;
                flag = temp;
                word[count++] = temp;
                while((temp = getc(file)) != EOF)
                {
                    if (temp == '\\')
                        escapeCount++;
                    else if (temp != flag)
                        escapeCount = 0;

                    if ((temp == flag && escapeCount % 2 == 0) || (temp == flag && escapeCount == 0))
                        break;

                    word[count++] = temp;
                }
            }
            else if (temp == '#') /* include */
            {
                word[count++] = temp;
                while((temp = getc(file)) != EOF && temp != '\n')
                {
                    word[count++] = temp;
                }
            } /* operators */
            else if (temp == '+' || temp == '-' || (temp == '*' && last != '/') || temp == '%'
            || temp == '>' || temp == '<' || temp == '!' || temp == '=' || temp == '&' || temp == '|')
            {
                last = temp;
                temp = getc(file);
                temp = ungetc(temp, file);
                if (temp == '=' || last == temp || (last == '-' && temp == '>' ))/* checks for doubles like a++ */
                {
                    word[count] = '\0';
                    count = 0;
                    list = addWord(list, word);
                    word[count++] = last;
                    word[count++] = temp;
                    temp = getc(file);
                }
                else
                {
                    word[count] = '\0';
                    count = 0;
                    list = addWord(list, word);
                    word[count++] = last;
                }
                word[count] = '\0';
                count = 0;
                list = addWord(list, word);
                dontPrint = 1;
            } /* comments or divides */
            else if (temp == '/' || temp == '*')
            {
                if (last == '/' && temp == '/') /* single line comment */
                {
                    word[count++] = last;
                    word[count++] = temp;
                    while((temp = getc(file)) != EOF && temp != '\n')
                    {
                        word[count++] = temp;
                    }
                    word[count++] = temp;
                }
                else if (last == '/' && temp == '*') /* multi line comment */
                {
                    word[count++] = last;
                    word[count++] = temp;
                    last = temp;
                    while((temp = getc(file)) != EOF && !(last == '*' && temp == '/'))
                    {
                        last = temp;
                        word[count++] = temp;
                    }
                    word[count++] = temp;
                    word[count++] = '\n';
                }
                else if (temp == '/') /* division */
                {
                    last = temp;
                    temp = getc(file);
                    temp = ungetc(temp, file);
                    if (temp == '/' || temp == '*')
                        continue;
                    else if (temp == '=')
                    {
                        word[count] = '\0';
                        count = 0;
                        list = addWord(list, word);
                        word[count++] = last;
                        word[count++] = temp;
                        temp = getc(file);
                    }
                    else
                    {
                        word[count] = '\0';
                        count = 0;
                        list = addWord(list, word);
                        word[count++] = last;
                    }
                }
                word[count] = '\0';
                count = 0;
                list = addWord(list, word);
                dontPrint = 1;
            }

            if(dontPrint == 0)
                word[count++] = temp;
        }
        dontPrint = 0;
        last = temp;
    }
    mainFunctions(list, fileName);
}
