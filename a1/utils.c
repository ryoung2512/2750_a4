#include "utils.h"

int isVariableType(char * str)
{
    if (strcmp("int", str) == 0 || strcmp("float", str) == 0||
        strcmp("double", str) == 0 || strcmp("char", str) == 0||
        strcmp("short", str) == 0 || strcmp("long", str) == 0 ||
        strcmp("void", str)== 0 || strcmp("unsigned", str) == 0 ||
         strcmp("signed", str) == 0)
        {
            return 1;
        }

    return 0;
}

int isPunct(char * str)
{
    if (strcmp(",", str) == 0 || strcmp(";", str) == 0||
        strcmp("(", str) == 0 || strcmp(")", str) == 0||
        strcmp("{", str) == 0 || strcmp("}", str) == 0 )
        {
            return 1;
        }

    return 0;
}

int isKeyword(char * str)
{
    if (strcmp("if", str) == 0 || strcmp("for", str) == 0 ||
        strcmp("while", str) == 0 || strcmp("switch", str) == 0)
        {
            return 1;
        }
    return 0;
}

int noSpace(char * str)
{
    if (strcmp("++", str) == 0 || strcmp(";", str) == 0 ||
        strcmp("--", str) == 0 || strcmp("[", str) == 0 ||
        strcmp("]", str) == 0)
        {
            return 1;
        }
    return 0;
}
