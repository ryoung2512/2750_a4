#include "list.h"

int addClosingBracket(Node * list, Node * theNode)
{
    Node * beforeFunc = findBeforeFunction(list, theNode);
    Node * newBracket = createRecord("}");
    insertAfter(beforeFunc, newBracket);
    Node * semiCol = createRecord(";");
    return insertAfter(newBracket, semiCol);
}

Node * addToBack(Node * theList, Node * toBeAdded)
{
    /* checks if list is empty if it is return head alone */
    if (isEmpty(theList) == 0)
    {
        Node * ptr = theList;
        int true = 1;

        /* loops through and finds back and adds the new list item to end */
        while(true)
        {
            if (ptr->next == NULL)
            {
                ptr->next = toBeAdded;
                toBeAdded->last = ptr;
                break;
            }
            ptr = ptr->next;
        }
        return theList;
    }
    else
    {
        return toBeAdded;
    }
}

Node * addToFront(Node * theList, Node * toBeAdded)
{
    /* checks if the list is empty or not, if it isnt assign next value to new head */
    if (isEmpty(theList) == 0)
    {
        toBeAdded->next = theList;
        theList->last = toBeAdded;
    }

    return toBeAdded;
}

int changeValue(Node * node, char * newValue, int size)
{
    if (node != NULL)
    {
        free(node->value); /* free the old value */
        node->value = malloc(sizeof(char) * size);
        strcpy(node->value, newValue);
        return 1;
    }
    return 0;
}

int containsFunction(Node * node)
{
    Node * ptr = node;
    Node * lastBracket = findLastBracket(node);
    char constStr[100];
    strcpy(constStr, "constructor");
    strcat(constStr, node->next->value);
    int true = 1;
    while(true)
    {
        /* if it finds a function that is not a constructor return 1 */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1 && strcmp(constStr, ptr->last->value) != 0)
            return 1;

        if (ptr->next == NULL || ptr->next == lastBracket)
            break;
        else
            ptr = ptr->next;
    }
    return 0;
}

void createConstructors(Node * head)
{
    Node * ptr = head;
    int true = 1, inClass = 0, brackets = 0;

    char varN[50];
    Node * placement = NULL;
    Node * openBracket = NULL;
    Node * firstFunction = NULL;

    while (true)
    {
        if (strcmp("{", ptr->value) == 0)
            brackets++;

        if (strcmp("}", ptr->value) == 0)
            brackets--;

        if (strcmp("class", ptr->value) == 0 && isClass(ptr) == 1)
        {
            placement = findLastBracket(ptr);

            /* ensures there are functions otherwise no point of having a constructor */
            if (containsFunction(ptr) == 0)
            {
                if (ptr->next != NULL)
                {
                    ptr = ptr->next;
                    continue;
                }
                else
                {
                    break;
                }
            }

            firstFunction = findBeforeFunction(head, ptr);
            if (placement != NULL)
            {
                /* Starts the constructor giving it the proper format */
                Node * type = createRecord("void");
                insertAfter(placement->last, type);
                char name[50];
                strcpy(name, "constructor");
                strcat(name, ptr->next->value);
                Node * constr = createRecord(name);
                insertAfter(type, constr);
                Node * firstBracket = createRecord("(");
                insertAfter(constr, firstBracket);
                Node * class = createRecord("class");
                insertAfter(firstBracket, class);
                Node * className = createRecord(ptr->next->value);
                insertAfter(class, className);
                char var[50];
                strcpy(var, "*");
                strcat(var, ptr->next->value);
                strcat(var, "var");
                strcpy(varN, ptr->next->value);
                strcat(varN, "var");
                Node * variable = createRecord(var);
                insertAfter(className, variable);
                Node * secondBracket = createRecord(")");
                insertAfter(variable, secondBracket);
                openBracket = createRecord("{");
                insertAfter(secondBracket, openBracket);
                brackets++;
            }
            inClass = 1;
        }

        if (brackets != 0  && inClass == 1)
        {
            /* Variable declarations inside of class */
            if (strcmp(ptr->value, "=") == 0 && whichComesFirst(head, ptr, firstFunction) == 1)
            {
                char temp[50];
                strcpy(temp, varN);
                strcat(temp,"->");;
                strcat(temp, ptr->last->value);
                Node * var = createRecord(temp);
                insertAfter(openBracket, var);
                Node * equals = createRecord("=");
                insertAfter(var, equals);

                Node * tempPtr = ptr->next;
                Node * spot = equals;
                /* Adds up to ; in constructor */
                while (true)
                {
                    Node * value = createRecord(tempPtr->value);
                    insertAfter(spot, value);
                    spot = value;
                    if (tempPtr->next == NULL || strcmp(tempPtr->next->value, ";") == 0)
                        break;
                    else
                        tempPtr = tempPtr->next;
                }
                Node * semiCol = createRecord(";");
                insertAfter(spot, semiCol);
                openBracket = semiCol;

                /* Removes from the struct/class and just leaves var; */
                Node * firstSemiCol = findFirstOccurence(ptr, ";");
                Node * ptr2 = ptr;
                while (true)
                {
                    if (ptr2->next == NULL || ptr2 == firstSemiCol)
                    {
                        break;
                    }
                    else
                    {
                        Node * temp = ptr2;
                        ptr2 = ptr2->next;

                        if (temp->last != NULL)
                            temp->last->next = temp->next;
                        if (temp->next != NULL)
                            temp->next->last = temp->last;
                        destroyRecord(temp);
                    }
                }

                ptr = firstSemiCol;
                continue;
            }

            if (isFunctionPtr(ptr) == 1)
            {
                char temp[50];
                strcpy(temp, varN);
                strcat(temp,"->");
                /* remove that pesky * in the front */
                char substr[30];
                memcpy(substr, &ptr->next->value[1], strlen(ptr->next->value));
                strcat(temp, substr);

                Node * deref = createRecord(temp);
                insertAfter(openBracket, deref);
                Node * equals = createRecord("=");
                insertAfter(deref, equals);
                Node * value = createRecord(substr);
                insertAfter(equals, value);
                Node * semiCol = createRecord(";");
                insertAfter(value, semiCol);
                /* just incase it has to run again it will know where to start */
                openBracket = semiCol;

                Node * endOfPtr = ptr->next->next->next->next->next->next;

                Node * firstRound =  findFirstOccurence(endOfPtr, ")");
                /* stops when it is no longer a function ptr */
                if (strcmp(firstRound->next->value, "(") != 0)
                {
                        Node * closingBracket = createRecord("}");
                        insertAfter(semiCol, closingBracket);
                }
            }
        }

        if(ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }

}

int createConstructorCalls(Node * head)
{
    Node * ptr = head;
    int true = 1, brackets = 0;
    char lastClass[50], lastFunction[50];
    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (brackets == 0)
        {
            lastClass[0] = 0;
            lastFunction[0] = 0;
        }

        /*  keeps track of the last class and the last function */
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
        {
            strcpy(lastClass, ptr->next->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            strcpy(lastFunction, ptr->last->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        /* checks if its a class call and that there is a constructor for that class otherwise no point calling the constructor */
        if (strcmp("class", ptr->value) == 0 && isClassCall(head, ptr) == 1 && constructorExists(head, ptr->next->value))
        {
            Node * firstCol = findFirstOccurence(ptr, ";");
            char * className = ptr->next->value;

            Node * spot = firstCol;
            Node * ptr2 = ptr->next->next;
            while (true)
            {
                if (strcmp(ptr2->value, ",") != 0 && strcmp(ptr2->value, "=") != 0 &&
                (ptr2->last->value != NULL && strcmp(ptr2->last->value, "=") != 0))
                {
                    if (strcmp(ptr2->value, "*") == 0)
                    {   /* handles malloc case works most of the time */
                        findMallocSpot(head, ptr2->next->value, lastClass, lastFunction, className);
                        if (ptr2->next->next == NULL || strcmp(ptr2->next->next->value, ";") == 0)
                            break;
                        else
                            ptr2 = ptr2->next->next;
                    }
                    else
                    {
                        if (brackets == 0) /* global class call */
                        {
                            findFunctionCalls(head, ptr2->value, className);
                        }
                        else
                        {
                            /* normal class call just create constructor on next line */
                            char temp[100];
                            strcpy(temp, "constructor");
                            strcat(temp, className);
                            Node * constructorCall = createRecord(temp);
                            insertAfter(spot, constructorCall);
                            Node * openingBracket = createRecord("(");
                            insertAfter(constructorCall, openingBracket);
                            temp[0] = 0;
                            strcpy(temp, "&");
                            strcat(temp, ptr2->value);
                            Node * parameter = createRecord(temp);
                            insertAfter(openingBracket, parameter);
                            Node * closingBracket = createRecord(")");
                            insertAfter(parameter, closingBracket);
                            Node * semiCol = createRecord(";");
                            insertAfter(closingBracket, semiCol);

                            spot = semiCol;
                        }
                    }

                }

                if (ptr2->next == NULL || ptr2->next == firstCol)
                    break;
                else
                    ptr2 = ptr2->next;
            }

            if (firstCol->next == NULL)
                break;
            else
                ptr = firstCol->next;
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }

    return 0;
}

void createFunctionPrototypes(Node * theList)
{
    Node * ptr = theList;
    int true = 1;
    while (true)
    {
        /* if function that is not main */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) && strcmp(ptr->last->value, "main") != 0)
        {
            /* if there is no prototype create it */
            if (hasPrototype(theList, ptr->last->value) == 0)
            {
                Node * ptr2 = getVariableTypeStart(theList, ptr);
                Node * spot = theList;
                while(true)
                {
                    Node * currentNode = createRecord(ptr2->value);
                    insertAfter(spot, currentNode);
                    spot = currentNode;
                    if (ptr2->next == NULL || strcmp(ptr2->next->value, "{") == 0)
                        break;
                    else
                        ptr2 = ptr2->next;
                }
                Node * semiCol = createRecord(";");
                insertAfter(spot, semiCol);

            }
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
    moveClassesToTop(theList);
}

Node * createRecord(char * value)
{
    /* allocates space for the size of the car struct */
    Node * node = malloc(sizeof(Node));

    if (node == NULL)
    {
        if (node != NULL)
            free(node);
        return(NULL);
    }
    else
    {
        /* allocates space for value */
        node->value = malloc(sizeof(char) * strlen(value) + 1);
        /* if it fails to allocate free appropriate memory */
        if (node->value == NULL)
        {
            free(node);
            return(NULL);
        }
        else
        {
            strcpy(node->value, value);
            node->next = NULL;
            node->last = NULL;
            return(node);
        }
    }
}

int constructorExists(Node * head, char * class)
{
    Node * ptr = head;
    int true = 1;

    char temp[50];
    strcpy(temp, "constructor");
    strcat(temp, class);
    while(true)
    {
        /* if it is right constructor return that it was found */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) && strcmp(temp, ptr->last->value) == 0)
            return 1;

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
    return 0;
}


void destroyList(Node * theList)
{
    Node * ptr = theList;
    Node * nextPtr;

    /*loops through and destroys each record in the list */
    while (ptr != NULL)
    {
        nextPtr = ptr->next;
        destroyRecord(ptr);
        ptr = nextPtr;
    }
}

void destroyRecord(Node * node)
{
    free(node->value);
    free(node);
}

void editFunctionCall(Node * theList, char * searchKey, char * class)
{
    Node * ptr = theList;
    int true = 1, brackets = 0;
    char search[50], usableVar[50], lastClass[50], lastFunction[50];
    Node * spot = NULL;
    strcpy(search, ".");
    strcat(search, searchKey);
    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (brackets == 0)
        {
            lastClass[0] = 0;
            lastFunction[0] = 0;
        }

        /* stores last class and last function */
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
        {
            strcpy(lastClass, ptr->next->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            strcpy(lastFunction, ptr->last->value);
            ptr = findFirstOccurence(ptr, "{");
            spot = ptr;
            continue;
        }

        if (strstr(ptr->value, search) != NULL && ptr->next != NULL && strcmp(ptr->next->value, "(") == 0)
        {
            char tempName[50];
            strcpy(tempName, ptr->value);
            strtok(tempName, ".");
            char * end = strtok(NULL, "");
            /* if it matches the token then find a usable var and create it */
            if (strcmp(end, searchKey) == 0)
            {
                strcpy(usableVar, findUsableVar(theList, lastClass, lastFunction, class));
                if (usableVar[0] == '\0')
                {
                    /* if there is no usable var make your own */
                    Node * theClassKeyword = createRecord("class");
                    insertAfter(spot, theClassKeyword);
                    Node * classVarKeyword = createRecord(class);
                    insertAfter(theClassKeyword, classVarKeyword);
                    char theVar[50];
                    strcpy(theVar, class);
                    strcat(theVar, "varFix");
                    strcpy(usableVar, theVar);
                    Node * variableName = createRecord(theVar);
                    insertAfter(classVarKeyword, variableName);
                    Node * semiCol = createRecord(";");
                    insertAfter(variableName, semiCol);
                }
                char temp[100];
                strcpy(temp, "&");
                strcat(temp, usableVar);
                Node * classVarNode = createRecord(temp);
                insertAfter(ptr->next, classVarNode);
                if (strcmp(classVarNode->next->value, ")") != 0)
                {
                    Node * comma = createRecord(",");
                    insertAfter(classVarNode, comma);
                }
            }
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}


Node * findBeforeFunction(Node * list, Node * node)
{
    int true = 1;
    Node * ptr = node;
    Node * beforeFunc = NULL;
    while(true)
    {
        /* finds the first function and then returns the start of the function */
        if (ptr->next == NULL || (strcmp(ptr->next->value, "(") == 0 && isFunction(ptr->next)))
        {
            if (ptr->next != NULL)
                beforeFunc = getVariableTypeStart(list, ptr->next)->last;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return beforeFunc;
}

Node * findFirstOccurence(Node * node, char * str)
{
    Node * ptr = node;
    int true = 1;
    while (true)
    {
        if (strcmp(ptr->value, str) == 0)
            return ptr;

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
    return NULL;
}

void findFunctionCalls(Node * head, char * search, char * className)
{
    Node * ptr = head;
    int true = 1;

    char searchTerm[50];
    strcpy(searchTerm, search);
    strcat(searchTerm, ".");
    while (true)
    {
        if (strstr(ptr->value, searchTerm) != NULL && ptr->next != NULL && strcmp(ptr->next->value, "(") == 0 && ptr->last != NULL)
        {
            /* creats the constructor call */
            Node * spot = findLastOccurence(ptr, "{");
            char temp[100];
            strcpy(temp, "constructor");
            strcat(temp, className);
            if (strcmp(spot->next->value, temp) != 0)
            {
                Node * constructorCall = createRecord(temp);
                insertAfter(spot, constructorCall);
                Node * openingBracket = createRecord("(");
                insertAfter(constructorCall, openingBracket);
                temp[0] = 0;
                strcpy(temp, "&");
                strcat(temp, search);
                Node * parameter = createRecord(temp);
                insertAfter(openingBracket, parameter);
                Node * closingBracket = createRecord(")");
                insertAfter(parameter, closingBracket);
                Node * semiCol = createRecord(";");
                insertAfter(closingBracket, semiCol);
            }
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

Node * findLastOccurence(Node * node, char * str)
{
    Node * ptr = node;
    int true = 1;
    while (true)
    {
        if (strcmp(ptr->value, str) == 0)
            return ptr;

        if (ptr->last == NULL)
            break;
        else
            ptr = ptr->last;
    }
    return NULL;
}

Node * findLastBracket(Node * node)
{
    Node * result = NULL;
    int true = 1, insideClass = 0;
    Node * ptr = findFirstOccurence(node, "{");
    while(true)
    {
        /* finds the last bracket of a function */
        if (strcmp("{", ptr->value) == 0)
            insideClass++;

        if (strcmp("}", ptr->value) == 0)
            insideClass--;

        if (ptr->next == NULL || insideClass == 0)
        {
            if (strcmp("}", ptr->value) == 0)
                result = ptr;
            break;
        }
        else
        {
            ptr = ptr->next;
        }
    }
    return result;
}

Node * findMallocSpot(Node * theList, char * search, char * class, char * function, char * className)
{
    /* this function is just incase there is a malloc and a consturctor for it */
    Node * ptr = theList;
    int true = 1, brackets = 0, replace = 0;
    char lastClass[50], lastFunction[50];
    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (brackets == 0)
        {
            lastClass[0] = 0;
            lastFunction[0] = 0;
        }
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
        {
            strcpy(lastClass, ptr->next->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            strcpy(lastFunction, ptr->last->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        if (strcmp(ptr->value, search) == 0 && ptr->next != NULL && ptr->next->next != NULL
        && strcmp(ptr->next->value, "=") == 0 && strcmp(ptr->next->next->value, "malloc") == 0)
        {
            if (class[0] == '\0' && function[0] == '\0') /* global */
                replace = 1;
            else if (class[0] != '\0' && function[0] != '\0' && strcmp(class, lastClass) == 0
                && strcmp(function, lastFunction) == 0) /* matches class and function */
                replace = 1;
            else if (class[0] != '\0' && strcmp(class, lastClass) == 0) /* matches class */
                replace = 1;
            else if (function[0] != '\0' && strcmp(function, lastFunction) == 0) /* matches function */
                replace = 1;

            if (replace == 1)
            {
                Node * spot = findFirstOccurence(ptr->next->next, ";");
                char temp[100];
                strcpy(temp, "constructor");
                strcat(temp, className);
                Node * constructorCall = createRecord(temp);
                insertAfter(spot, constructorCall);
                Node * openingBracket = createRecord("(");
                insertAfter(constructorCall, openingBracket);
                temp[0] = 0;
                strcpy(temp, search);
                Node * parameter = createRecord(temp);
                insertAfter(openingBracket, parameter);
                Node * closingBracket = createRecord(")");
                insertAfter(parameter, closingBracket);
                Node * semiCol = createRecord(";");
                insertAfter(closingBracket, semiCol);
                replace = 0;
            }
        }
        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
    return NULL;
}


char * findUsableVar(Node * theList, char * classLocation, char * functionLocation, char * class)
{
    Node * ptr = theList;
    int true = 1, brackets = 0;
    char lastClass[50], lastFunction[50];

    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (brackets == 0)
        {
            lastClass[0] = 0;
            lastFunction[0] = 0;
        }
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
        {
            strcpy(lastClass, ptr->next->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            strcpy(lastFunction, ptr->last->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        /* if it finds a usable var return the value */
        if (strcmp("class", ptr->value) == 0 && isClassCall(theList, ptr) == 1 && strcmp(ptr->next->value, class) == 0)
        {
            if (lastClass[0] == '\0' && lastFunction[0] == '\0')
                return ptr->next->next->value;
            else if (strcmp(lastClass, classLocation) == 0 && strcmp(lastFunction, functionLocation) == 0)
                return ptr->next->next->value;
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
    return NULL;
}

void finishFunctionCalls(Node * theList)
{
    Node * ptr = theList;
    int true = 1, brackets = 0;
    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;

        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) && brackets == 1)
        {
            /* finds out if there is a struct passed into a function and if so edits the function calls */
            Node * beforeBracket = findFirstOccurence(ptr, ")")->last;
            if (strcmp(ptr->next->value, "class") == 0 && strstr(beforeBracket->value, "var") != NULL)
            {
                char * className = ptr->next->next->value;
                editFunctionCall(theList, ptr->last->value, className);
            }
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

void fixAnyOtherCalls(Node * theList, char * search, char * prefix)
{
    Node * ptr = theList;
    int true = 1, brackets = 0;
    char lastClass[50], lastFunction[50];
    while(true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (brackets == 0)
        {
            lastClass[0] = 0;
            lastFunction[0] = 0;
        }
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
        {
            strcpy(lastClass, ptr->next->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            strcpy(lastFunction, ptr->last->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        /* fixes any other cals that were not  fixed in a . function call */
        if (strcmp(ptr->value, search) == 0 && strcmp(ptr->next->value, "(")== 0 && strcmp(lastClass, prefix) == 0)
        {
            if (isFunction(ptr->next) == 0)
            {
                char temp[50];
                strcpy(temp, prefix);
                strcat(temp, search);
                Node * ptr2 = ptr->next->next;
                char suffix[20];
                suffix[0] = 0;
                int count = 0;
                while (true)
                {
                    if (strcmp(ptr2->value, ",") != 0)
                    {
                        /* gets the suffix */
                        char type[50];
                        getVarType(theList, ptr2->value, lastClass, lastFunction, ptr2, type);
                        int i;
                        for (i = 0; i < strlen(type); i++)
                        {
                            suffix[count++] = type[i];
                        }
                    }

                    if (ptr2->next == NULL || strcmp(ptr2->next->value, ")") == 0)
                        break;
                    else
                        ptr2 = ptr2->next;
                }
                suffix[count] = '\0';
                strcat(temp, suffix);
                changeValue(ptr, temp, 100);
            }
        }
        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}


void fixBrackets(Node * theList)
{
    Node * ptr = theList;

    int true = 1;
    while(true)
    {
        if (strcmp("class", ptr->value) == 0 && isClass(ptr) == 1)
        {
            if (containsFunction(ptr) == 0)
            {
                if (ptr->next != NULL)
                {
                    ptr = ptr->next;
                    continue;
                }
                else
                {
                    break;
                }
            }
            Node * lastBracket = findLastBracket(ptr);
            if (lastBracket != NULL)
            {    /* removes the last bracket */
                Node * following = lastBracket->next;
                if (following != NULL && strcmp(following->value, ";") != 0)
                {
                    lastBracket->last->next = following;
                    lastBracket->next->last = lastBracket->last;
                }
                else if (following != NULL && strcmp(following->value, ";") == 0)
                {
                    lastBracket->last->next = following->next;
                    if (following->next != NULL)
                        following->next->last = lastBracket->last;
                    destroyRecord(following);
                }
                destroyRecord(lastBracket);
            }
            /* adds the bracket at the new "appropriate" spot */
            addClosingBracket(theList, ptr);
        }

        if (ptr->next != NULL)
            ptr = ptr->next;
        else
            break;
    }
}

void fixClassVariables(Node * theList)
{
    Node * ptr = theList;
    Node * class = NULL;
    Node * end = NULL;
    int true = 1, edit = 0, hitEquals = 0, brackets = 0;
    while(true)
    {
        if (strcmp(ptr->value, "{"))
            brackets++;
        else if (strcmp(ptr->value, "}"))
            brackets--;

        /* finds class stores end of class */
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr))
        {
            end = findLastBracket(ptr);
            class = ptr;
        }

        /* finds function and resets values */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr))
        {
            if (end != NULL && end->next != NULL)
            {
                ptr = end->next;
                end = NULL;
                class = NULL;
                brackets = 0;
            }
        }

        /* resets values when it hit something */
        if (strcmp(ptr->value, ";") == 0 || strcmp(ptr->value, ")") == 0 ||
            (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1))
        {
            edit = 0;
            hitEquals = 0;
        }

        if (edit == 1 && strcmp(ptr->value, "=") == 0)
            hitEquals = 1;

        if (hitEquals == 1 && strcmp(ptr->value, ",") == 0)
            hitEquals = 0;


        if (edit == 1 && isVariableType(ptr->value) == 0 && isPunct(ptr->value) == 0
             && hitEquals == 0 && class != NULL)
             {
                fixFunctionVariables(theList, class, ptr->value);
             }

        if (isVariableType(ptr->value) == 1 && isFunctionPtr(ptr->next) != 1 && brackets != 0)
        {
            Node * firstRound =  findFirstOccurence(ptr, "(");
            Node * firstSemi = findFirstOccurence(ptr, ";");

            if (whichComesFirst(theList, firstSemi, firstRound) == 1)
                edit = 1;
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

void fixCalls(Node * theList, char * searchTerm, char * prefix)
{
    Node * ptr = theList;
    int true = 1, brackets = 0;
    char search[100], lastClass[50], lastFunction[50];
    strcpy(search, ".");
    strcat(search, searchTerm);
    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (brackets == 0)
        {
            lastClass[0] = 0;
            lastFunction[0] = 0;
        }

        /* stores class and skips to the { */
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
        {
            strcpy(lastClass, ptr->next->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        /* stores function and skips to the { */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            strcpy(lastFunction, ptr->last->value);
            ptr = findFirstOccurence(ptr, "{");
            continue;
        }

        /* finds the search term and sets the value when it finds a . version */
        if (strstr(ptr->value, search) != NULL && ptr->next != NULL && strcmp(ptr->next->value, "(") == 0)
        {
            char * start = strtok(ptr->value, ".");
            char temp[100];
            strcpy(temp, start);
            strcat(temp, ".");
            strcat(temp, prefix);
            strcat(temp, searchTerm);

            if (ptr->next->next != NULL && strcmp(ptr->next->next->value, ")") == 0)
            {
                changeValue(ptr, temp, 100);
            }
            else
            {
                Node * ptr2 = ptr->next->next;
                char suffix[20];
                suffix[0] = 0;
                int count = 0;
                while (true)
                { /* sets suffix */
                    if (strcmp(ptr2->value, ",") != 0)
                    {
                        char type[50];
                        getVarType(theList, ptr2->value, lastClass, lastFunction, ptr2, type);
                        int i;
                        for (i = 0; i < strlen(type); i++)
                        {
                            suffix[count++] = type[i];
                        }
                    }

                    if (ptr2->next == NULL || strcmp(ptr2->next->value, ")") == 0)
                        break;
                    else
                        ptr2 = ptr2->next;
                }
                suffix[count] = '\0';
                strcat(temp, suffix);
                changeValue(ptr, temp, 100);

            }
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

void fixFunctionCalls(Node * theList)
{
    Node * ptr = theList;
    int true = 1, brackets = 0;
    char prefix[30];

    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;

        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1)
            strcpy(prefix, ptr->next->value);

       /* finds a function then calls fix calls */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1 && brackets == 1)
        {
            fixCalls(theList, ptr->last->value, prefix);
        }

        if(ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

void fixFunctionPtrs(Node * theList)
{
    Node * ptr = theList;
    int true = 1;
    while (true)
    {
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1)
        {
            char temp[50];
            strcpy(temp, "*");
            strcat(temp, ptr->last->value);
            fixPtr(theList, temp, ptr);
        }
        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

int fixFunctionVariables(Node * list, Node * class, char * var)
{
    if (containsFunction(class) == 0)
        return 0;

    Node * ptr = findBeforeFunction(list, class);
    Node * end = findLastBracket(class);
    Node * header = NULL;
    int true = 1, skip = 0, changed = 0;
    while (true)
    {
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr))
        {
            skip = 0;
            header = ptr;
        }

        if (strcmp(ptr->value, var) == 0 && ptr->last != NULL && (isVariableType(ptr->last->value) == 1
        || strcmp(ptr->last->value, "class") == 0 || (strcmp(ptr->last->value, "*") == 0 && ptr->last->last != NULL
        && (isVariableType(ptr->last->last->value) || strcmp(ptr->last->value, "class") == 0)) ) )
        {
            skip = 1;
        }

        if (strcmp(ptr->value, var) == 0 && skip == 0)
        {
            char temp[50];
            strcpy(temp, class->next->value);
            strcat(temp, "var");
            strcat(temp, "->");
            strcat(temp, ptr->value);
            changeValue(ptr, temp, 50);

            if (strcmp(header->next->value, "class") != 0)
            {
                Node * classVar = createRecord("class");
                insertAfter(header, classVar);
                Node * className = createRecord(class->next->value);
                insertAfter(classVar, className);
                strcpy(temp, "*");
                strcat(temp, class->next->value);
                strcat(temp, "var");
                Node * varName = createRecord(temp);
                insertAfter(className, varName);
                if (strcmp(varName->next->value, ")") != 0)
                {
                    Node * comma = createRecord(",");
                    insertAfter(varName, comma);
                }
                changed = 1;
            }
        }

        if (ptr->next == NULL || ptr->next == end)
            break;
        else
            ptr = ptr->next;
    }
    return changed;
}

void fixPtr(Node * theList, char * search, Node * start)
{
    Node * ptr = theList;
    int true = 1;
    while (true)
    {
        /* if it is ptr name add from start to ) */
        if (isFunctionPtr(ptr) == 1)
        {
            if (strcmp(ptr->next->value, search) == 0)
            {
                Node * spot = findFirstOccurence(ptr->next, "(");
                Node * ptr2 = start->next;
                if (strcmp(ptr2->value, ")") != 0)
                {
                    while (true)
                    {
                        Node * temp = createRecord(ptr2->value);
                        insertAfter(spot, temp);
                        spot = temp;

                        if (ptr2->next == NULL || strcmp(ptr2->next->value, ")") == 0)
                            break;
                        else
                            ptr2 = ptr2->next;
                    }
                }

                break;
            }
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
}

Node * getLastItem(Node * theList)
{
    if (theList == NULL)
        return(NULL);
    else
    {
        Node * ptr = theList;
        int true = 1;

        /* finds the last item in the list by looping through */
        while (true)
        {
            if (ptr->next == NULL)
                break;

            ptr = ptr->next;
        }
        return ptr;
    }
}

void getSuffix(Node * node, char * suffix)
{
    Node * ptr = node;
    int true = 1, count = 0;

    /* suffix returns as null if there is no parameters */
    while(true)
    {
        if (isVariableType(ptr->value) == 1)
        {
            suffix[count++] = ptr->value[0];
        }

        if (ptr->next != NULL && strcmp(")", ptr->next->value) != 0)
            ptr = ptr->next;
        else
            break;
    }

    suffix[count] = '\0';
}

Node * getVariableTypeStart(Node * theList, Node * theNode)
{
    Node * lastCurlyStart = findLastOccurence(theNode->last, "{");
    Node * lastCurlyEnd = findLastOccurence(theNode->last, "}");
    Node * lastSemiCol = findLastOccurence(theNode->last, ";");

    Node * ptr = theNode->last->last;
    int true = 1;
    while(true)
    {
        /* looks for certain patterns in the characters and see if it can find it */
        if (ptr->last == NULL || ptr->last == lastCurlyStart || ptr->last == lastCurlyEnd || ptr->last == lastSemiCol
        || strstr(ptr->last->value, "//") != NULL || strstr(ptr->last->value, "/*") != NULL)
        {
            return ptr;
            break;
        }
        else
            ptr = ptr->last;
    }
    return NULL;
}

void getVarType(Node * theList, char * var, char * class, char * function, Node * used, char * type)
{
    Node * ptr = theList;
    int true = 1, inClass = 0, brackets = 0, inFunction = 0;
    char lastVar[50];
    type[0] = '\0';
    while (true)
    {
        if (strcmp(ptr->value, "{") == 0)
            brackets++;
        if (strcmp(ptr->value, "}") == 0)
            brackets--;

        if (strcmp(ptr->value, "class") == 0 && isClass(ptr) == 1 && strcmp(ptr->next->value, class) == 0)
            inClass = 1;

        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1 && strcmp(ptr->last->value, function) == 0)
            inFunction = 1;

        if (isVariableType(ptr->value) == 1)
        {
            Node * firstRound =  findFirstOccurence(ptr, "(");
            Node * firstSemi = findFirstOccurence(ptr, ";");

            if (whichComesFirst(theList, firstSemi, firstRound) == 1)
            {
                /* stores the first letter of each var and adds it */
                Node * ptr2 = ptr;
                int count = 0;
                while(true)
                {
                    if (ptr2->next == NULL || isVariableType(ptr2->value) == 0)
                        break;
                    else
                    {
                        lastVar[count++] = ptr2->value[0];
                        ptr2 = ptr2->next;
                    }
                }
                lastVar[count] = '\0';
            }
        }

        if (strcmp(ptr->value, ";") == 0 || strcmp(ptr->value, ")") == 0)
            lastVar[0] = 0;

        if (strcmp(ptr->value, var) == 0 && lastVar[0] != '\0')
        {
            type[0] = 0;
            if (brackets == 0)
                strcpy(type, lastVar);
            else if (inClass == 1 && inFunction == 1)
                strcpy(type, lastVar);
            else if (inClass == 1)
                strcpy(type, lastVar);
            else if (inFunction == 1)
                strcpy(type, lastVar);

        }

        if (ptr->next == NULL || ptr->next == used)
            break;
        else
            ptr = ptr->next;
    }
}

int hasPrototype(Node * theList, char * search)
{
    Node * ptr = theList;
    int true = 1;
    while (true)
    {
        /* sees if it matches prototype */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) && strcmp(ptr->last->value, search) == 0)
        {
            Node * lastBracket = findFirstOccurence(ptr, ")");
            if (lastBracket->next != NULL && strcmp(lastBracket->next->value, ";") == 0)
                return 1;
        }
        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }
    return 0;
}

int insertAfter(Node * node, Node * newNode)
{
    if (node == NULL || newNode == NULL)
        return 0;

    Node * temp = node->next;
    node->next = newNode;
    newNode->next = temp;
    newNode->last = node;
    if (temp != NULL)
        temp->last = newNode;
    return 1;
}

int isClass(Node * theNode)
{
    if (theNode->next != NULL && theNode->next->next != NULL)
    {
        /* looks for class pattern */
        if (isPunct(theNode->next->value) == 0 && strcmp("{", theNode->next->next->value) == 0)
        {
            return 1;
        }
    }
    return 0;
}


int isClassCall(Node * theList, Node * theNode)
{
    if (theNode->next != NULL && theNode->next->next != NULL && theNode->next->next->next != NULL)
    {
        /* looks for class call pattern */
        if (isPunct(theNode->next->value) == 0 && strcmp("{", theNode->next->next->value) != 0 &&
             strcmp(")", theNode->next->next->next->value) != 0)
        {
            if (strcmp(";", theNode->next->next->next->value) != 0)
            {
                Node * firstRoundBracket = findFirstOccurence(theNode, ")");
                Node * firstSemiCol = findFirstOccurence(theNode, ";");
                if (whichComesFirst(theList, firstRoundBracket,firstSemiCol) == 2)
                    return 1;
                else
                    return 0;
            }
            return 1;
        }
    }
    return 0;
}

int isEmpty(Node * theList)
{
    if (theList != NULL)
        return 0;

    return 1;
}

int isFunction(Node * theNode)
{
    /* looks for function patterm */
    Node * firstCloseBracket = findFirstOccurence(theNode, ")");
    if (firstCloseBracket != NULL && firstCloseBracket->next != NULL &&
        strcmp(firstCloseBracket->next->value, "{") == 0 && theNode->last != NULL
        && isKeyword(theNode->last->value) == 0)
    {
        return 1;
    }
    return 0;
}


int isFunctionCall(Node * theNode)
{
    if (theNode->next != NULL && theNode->next != NULL && theNode->last != NULL)
    {
        /* looks for function call pattern */
        if (isPunct(theNode->value) == 0 && strcmp("(", theNode->next->value) == 0
        && isVariableType(theNode->last->value) == 0)
        {
            return 1;
        }
    }
    return 0;
}

int isFunctionPtr(Node * theNode)
{
    if (theNode->next != NULL && theNode->next->next != NULL && theNode->next->next->next != NULL &&
        theNode->next->next->next->next != NULL)
    {
        if (strcmp("(", theNode->value) == 0 && isVariableType(theNode->next->value) == 0 &&
            isPunct(theNode->next->value) == 0 && strcmp(")", theNode->next->next->value) == 0
            && strcmp("(", theNode->next->next->next->value) == 0 &&
            strcmp(")", theNode->next->next->next->next->value) == 0 )
            {
                return 1;
            }
    }
    return 0;
}

void moveClassesToTop(Node * theList)
{
    Node * ptr = theList;
    int true = 1;
    Node * spot = theList;
    while (true)
    {
        if (strcmp(ptr->value, "class") == 0 && isClass(ptr))
        {
            Node * lastBracket = findLastBracket(ptr)->next;
            Node * ptr2 = ptr;

            /* inserts them at top */
            while(true)
            {
                Node * newRecord = createRecord(ptr2->value);
                insertAfter(spot, newRecord);
                spot = newRecord;
                if (ptr2->next == NULL || ptr2 == lastBracket)
                    break;
                else
                    ptr2 = ptr2->next;
            }

            Node * end = findLastBracket(ptr)->next->next;
            ptr2 = ptr;
            while (true)
            {
                if (ptr2 == NULL || ptr2->next == NULL || ptr2 == end)
                {
                    break;
                }
                else
                {
                    Node * temp = ptr2;
                    ptr2 = ptr2->next;

                    if (temp->last != NULL)
                        temp->last->next = temp->next;
                    if (temp->next != NULL)
                        temp->next->last = temp->last;
                    destroyRecord(temp);
                }
            }
            ptr = end;
            continue;
        }

        if (ptr->next == NULL)
            break;
        else
            ptr = ptr->next;
    }

}

void printList(Node * theList, char * fileName)
{
    FILE * file = fopen(fileName, "w");
    Node * ptr = theList;
    int true = 1, tabs = 0, inLoop = 0;
    /* loops through and prints out each message in the list */
    while(true)
    {
        if (strcmp("{", ptr->value) == 0)
            tabs = tabs + 4;

        if (strcmp("}", ptr->value) == 0)
            tabs = tabs - 4;

        if (strcmp(ptr->value, "for") == 0)
            inLoop = 1;

        if (inLoop == 1 && strcmp(ptr->value, ")") == 0)
            inLoop = 0;

        printRecord(ptr, tabs, inLoop, file);

        if (ptr->next != NULL)
            ptr = ptr->next;
        else
            break;
    }
    fclose(file);
    printf("Wrote program to %s\n", fileName);
}

void printRecord(Node * node, int tabs, int inLoop, FILE * file)
{
    if (node != NULL)
    {
        char lastChar = node->value[strlen(node->value) - 1];

        /*printf("%s", node->value);*/
        fprintf(file, "%s", node->value);

        if (node->next != NULL && noSpace(node->next->value) == 0
            && noSpace(node->value) == 0 && lastChar != '\n')
            {
                /*printf(" ");*/
                fprintf(file, " ");
            }

        if (inLoop == 1 && strcmp(node->value, ";") == 0)
        {
            /*printf(" ");*/
            fprintf(file, " ");
        }

        if ((strcmp(node->value, ";") == 0 || strcmp(node->value, "{") == 0 ||
            strcmp(node->value, "}") == 0 || lastChar == '\n') && inLoop == 0)
            {
                if (node->next != NULL && strcmp(node->next->value, ";") != 0
                && lastChar != '\n')
                {
                    /*printf("\n");*/
                    fprintf(file, "\n");
                }

                if (node->next != NULL && strcmp(node->next->value, "}") == 0)
                    tabs = tabs - 4;

                int i;
                for (i = 0; i < tabs; i++)
                {
                    /*printf(" ");*/
                    fprintf(file, " ");
                }

                if (node->next == NULL)
                {
                    /*printf("\n");*/
                    fprintf(file, "\n");
                }

            }

    }
}

Node * removeBetween(Node * node)
{
    if (node != NULL)
    {
        Node * temp = node->next;
        node->last->next = node->next;
        node->next->last = node->last;
        destroyRecord(node);
        return temp;
    }
    return NULL;
}

void renameFunctions(Node * theList)
{
    Node * currentClass = NULL;
    Node * ptr = theList;
    int true = 1, insideClass = 0;
    char prefix[50];
    while(true)
    {
        if (strcmp("{", ptr->value) == 0)
            insideClass++;

        if (strcmp("}", ptr->value) == 0)
            insideClass--;

        if (strcmp("class", ptr->value) == 0 && isClass(ptr))
        {
            strcpy(prefix, ptr->next->value);
            currentClass = ptr->next->next;
        }

        /* if it finds a function perform operation */
        if (strcmp(ptr->value, "(") == 0 && isFunction(ptr) == 1 && insideClass != 0)
        {
            char suffix[20];
            getSuffix(ptr, suffix);
            char temp[100] = "";
            strcat(temp, prefix);
            strcat(temp, ptr->last->value);
            strcat(temp, suffix);
            fixAnyOtherCalls(theList, ptr->last->value, prefix);
            changeValue(ptr->last, temp, 100); /* renames it */


            Node * beforeFunction = findBeforeFunction(theList, currentClass);
            Node * variableType = getVariableTypeStart(theList, ptr);
            Node * ptr2 = variableType;
            Node * spot = beforeFunction;
            while (true)
            {
                Node * type = createRecord(ptr2->value);
                insertAfter(spot, type);
                spot = type;
                if (ptr2->next == NULL || ptr2->next == ptr->last)
                    break;
                else
                    ptr2 = ptr2->next;
            }
            /* creates function ptr */
            Node * firstBracket = createRecord("(");
            insertAfter(spot, firstBracket);
            char anotherTemp[150];
            anotherTemp[0] = 0;
            strcat(anotherTemp, "*");
            strcat(anotherTemp, temp);
            Node * fName = createRecord(anotherTemp);
            insertAfter(firstBracket, fName);
            Node * secondBracket = createRecord(")");
            insertAfter(fName, secondBracket);
            Node * thirdBracket = createRecord("(");
            insertAfter(secondBracket, thirdBracket);
            Node * lastBracket = createRecord(")");
            insertAfter(thirdBracket, lastBracket);
            Node * semiCol = createRecord(";");
            insertAfter(lastBracket, semiCol);

        }

        if (ptr->next != NULL)
            ptr = ptr->next;
        else
            break;
    }
}

int replaceRecord(Node * theList, char * find, char * replace)
{
    int replaced = 0, true = 1;
    Node * ptr = theList;
    while(true)
    {
        if (strcmp(ptr->value, find) == 0)
            replaced = changeValue(ptr, replace, 100);

        if (ptr->next != NULL)
            ptr = ptr->next;
        else
            break;
    }
    return replaced;
}

int whichComesFirst(Node * theList, Node * firstNode, Node * secondNode)
{
    Node * ptr = theList;
    int true = 1, countOne = 0, countTwo = 0;
    /* counts the location in the list part 1 */
    while (true)
    {
        countOne++;
        if (ptr->next == NULL || ptr->next == firstNode)
            break;
        else
            ptr = ptr->next;
    }
    ptr = theList;
    /* counts the location in list part 2 */
    while (true)
    {
        countTwo++;
        if (ptr->next == NULL || ptr->next == secondNode)
            break;
        else
            ptr = ptr->next;
    }

    if (countOne < countTwo)
        return 1;
    else if (countOne > countTwo)
        return 2;
    else
        return 0;
}
