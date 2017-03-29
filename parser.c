#include "parser.h"

void chooseType(char type, char ** characteristics, int position, char ** arguments, int args)
{
    switch (type)
    {
        case 'h':
            header(characteristics, position);
            break;
        case 'b':
            button(characteristics, position, arguments, args);
            break;
        case 'c':
            createPost(characteristics, position, arguments, args);
            break;
        case 'd':
            printf("<hr>\n");
            break;
        case 'e':
            execute(characteristics, position);
            break;
        case 'i':
            input(characteristics, position, arguments, args);
            break;
        case 'l':
            html_link(characteristics, position);
            break;
        case 'p':
            image(characteristics, position);
            break;
        case 'r':
            radio(characteristics, position);
            break;
        case 'k': /* add author */
            addAuthor(characteristics, position, arguments, args);
            break;
        case 't':
            text(characteristics, position);
            break;
        case 'T':
            textArea(characteristics, position);
            break;
        default:
            break;

    }
}

void freeArrayElements(char ** characteristics, int position)
{
    int i;
    for (i = 0; i < position; i++) free(characteristics[i]);
}

void readFile(FILE * input, char * filename, char ** arguments, int args)
{
    startFile("Rhys's A4 Assignment For 2750");
    char ** characteristics = malloc(sizeof(char *) * 20);
    int bracketCount = 0, escaped = 0, count = 0, inString = 0, position = 0, firstFound = 0;
    char last = 0, current, type = 0, next = 0;
    if (args >= 5)
    {
        char username[50], stream[50], counter[50], limit[50], sorted[50];
        concatenateArgs(arguments, args, username, stream, counter, limit, sorted);
        printf("Logged in as: <b>%s</b>, your current stream is: <b>%s</b>.\n", username, stream);
    }
    char str[100];
    while ((current = getc(input)) != EOF)
    {
        next = getc(input);
        ungetc(next, input);
        if ((current == '(' || current == ')') && inString == 0) /* bracket count */
        {
            if (current == ')' && bracketCount == 1)
            {
                str[count] = '\0';
                if (str[0] != '\0')
                {
                    characteristics[position] = malloc(sizeof(char) * count + 1);
                    strcpy(characteristics[position++], str);
                }
                count = 0;
            }
            if (current == '(') bracketCount++;
            else bracketCount--;
            last = current;
        }
        else if (current == ',' && inString == 0 && bracketCount == 1)
        {
            str[count] = '\0';
            characteristics[position] = malloc(sizeof(char) * count + 1);
            strcpy(characteristics[position++], str);
            count = 0;
        }
        else if (current == '"')
        {
            if (inString == 0) inString = 1;
            else if (escaped % 2 == 0 && inString == 1) inString = 0;
            str[count++] = current;
            escaped = 0;
        }
        else if (bracketCount == 1)
        {
            if (inString == 1 && current == '\\')
                escaped++;
            else if (inString == 1)
                escaped = 0;
            if (inString == 0 && current == ' ')
                continue;
            str[count++] = current;
        }
        else if ((current == '\n' || (bracketCount == 0 && last == '.' && firstFound == 1)) && type != 0)
        {
            chooseType(type, characteristics, position, arguments, args);
            freeArrayElements(characteristics, position);
            position = count = bracketCount = 0;
            if (current == '\n') firstFound = last = type = 0;
        }

        if (next == EOF && type != 0)
        {
            chooseType(type, characteristics, position, arguments, args);
            freeArrayElements(characteristics, position);
            position = count = bracketCount = 0;
            if (current == '\n') firstFound = last = type = 0;
        }


        if (bracketCount == 0 && last == '.') /* the type */
        {
            firstFound = 1;
            type = current;
        }
        last = current;
    }
    freeArrayElements(characteristics, position);
    free(characteristics);
    if (strcmp(filename, "header") != 0
     && strcmp(filename,"mark_all") != 0
     && strcmp(filename, "authorcontrol") != 0
      && strcmp(filename,"choose") != 0)
      {
         endFile();
      }
}

int main(int argc, char const *argv[]) {
    char input[50], output[50];
    char ** arguments = malloc(sizeof(char * ) * (argc - 2));
    char * filename;
    /* check to make sure arguements are right */
    if (argc < 2)
    {
        printf("Invalid number of arguements...exiting\n");
        exit(1);
    }
    strcpy(input, argv[1]);
    if (argc > 2)
    {
        /* fetches the author then removes everything else */
        int i, count = 0;
        for (i = 2; i < argc; i++)
        {
            arguments[count] = malloc(sizeof(char) * strlen(argv[i]) + 1);
            strcpy(arguments[count++], argv[i]);
        }
    }
    /* check to make sure file opened okay */
    FILE * f = fopen(argv[1], "r");
    if (f == NULL)
    {
        printf("Failed to open file.. exiting\n");
        exit(1);
    }
    /* set filename and output variables */
    filename = strtok(input, ".");
    strtok(NULL, "");
    strcpy(output, filename);
    strcat(output, ".html");
    if (argc > 2)
        readFile(f, filename, arguments, argc - 2);
    else
        readFile(f, filename, NULL, argc - 2);

    if (argc > 2)
    {
        int j = 0;
        for (j = 0; j < argc - 2; j++)
            free(arguments[j]);
    }
    fclose(f);
    free(arguments);
    return 0;
}
