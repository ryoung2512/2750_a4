#include "stream.h"

int addUser(char * username, char * list)
{
    char * stream = strtok(list, ",");
    while (stream != NULL)
    {
        char temp[200];
        sprintf(temp, "./db -addauthor \"%s\" \"%s\"", username, stream);
        system(temp);
        stream = strtok(NULL, ",");
    }
    return 0;
}

int removeUser(char * username, char * list)
{
    char * stream = strtok(list, ",");
    while (stream != NULL)
    {
        char temp[200];
        sprintf(temp, "./db -removeA \"%s\" \"%s\"", username, stream);
        system(temp);
        stream = strtok(NULL, ",");
    }
    return 0;
}

int updateStream(struct userPost * st)
{
    if (st->text[strlen(st->text) - 1] == '\n')
        st->text[strlen(st->text) - 1] = '\0';
    char temp[200];
    sprintf(temp, "./db -post \"%s\" \"%s\" \"%s\" \"%s\"", st->username, st->streamname, st->date, st->text);
    system(temp);
    return 0;
}
