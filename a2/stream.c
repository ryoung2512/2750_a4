#include "stream.h"

int addUser(char * username, char * list)
{
    FILE * f;
    char * stream = strtok(list, ",");
    int found = 0;
    while (stream != NULL)
    {
        if (stream != NULL)
        {
            /* creates file name */
            char streamUsers[70];
            strcpy(streamUsers, "a2/messages/");
            strcat(streamUsers, stream);
            strcat(streamUsers, "StreamUsers");
            f = fopen(streamUsers, "r");

            if (f == NULL)
            {
                char mainStream[70];
                strcpy(mainStream, "a2/messages/");
                strcat(mainStream, stream);
                strcat(mainStream, "Stream");

                FILE * temp;
                temp = fopen(mainStream, "a");
                fclose(temp);

                char streamData[70];
                strcpy(streamData, "a2/messages/");
                strcat(streamData, stream);
                strcat(streamData, "StreamData");

                temp = fopen(streamData, "a");
                fclose(temp);
            }
            else
            {
                fclose(f);
            }

            f = fopen(streamUsers, "r");
            if (f != NULL)
            {
                char word[50], user[100];
                strcpy(user, "");
                char ch;

                /* check if it already exists */
                while (fscanf(f, "%s%c", word, &ch) != EOF)
                {
                    if (ch != '\n')
                    {
                        strcat(user, word);
                        char c[2];
                        c[0] = ch;
                        c[1] = '\0';
                        strcat(user, c);
                    }
                    else
                    {
                        user[strlen(user) - 1] = '\0';
                        if (strcmp(user, username) == 0)
                        {
                            found = 1;
                            break;
                        }
                        user[0] = 0;
                    }
                }
                fclose(f);
            }

            f = fopen(streamUsers, "a");
            if (found == 0)
            {
                fprintf(f, "%s 0\n", username);
                printf("Succesfully added %s to %s!<br>", username, stream);
            }
            else
                printf("Error: username already existed in %s - not added<br>", stream);
            fclose(f);
            found = 0;
        }
        stream = strtok(NULL, ",");
    }

    return 0;
}

int removeUser(char * username, char * list)
{
    FILE * f;
    char * stream = strtok(list, ",");
    while (stream != NULL)
    {
        int removed = 0;
        if (stream != NULL)
        {
            /* creates file name */
            char streamUsers[70];
            strcpy(streamUsers, "a2/messages/");
            strcat(streamUsers, stream);
            strcat(streamUsers, "StreamUsers");
            f = fopen(streamUsers, "r");

            /* have to check to make sure it exists because we are removing not adding */
            if (f != NULL)
            {
                /* counts lines */
                int lines = 0, temp;

                do {
                    temp = fgetc(f);
                    if (temp == '\n')
                        lines++;
                } while(temp != EOF);


                char ** fileArray = malloc(sizeof(char *) * lines);

                rewind(f);

                char word[50], user[100];
                strcpy(user, "");
                int count = 0;
                char ch;

                /* loop through storing in array, if it finds the value dont store it */
                while (fscanf(f, "%s%c", word, &ch) != EOF)
                {
                    if (ch != '\n')
                    {
                        strcat(user, word);
                        char c[2];
                        c[0] = ch;
                        c[1] = '\0';
                        strcat(user, c);
                    }
                    else
                    {
                        user[strlen(user) - 1] = '\0';
                        if (strcmp(user, username) != 0)
                        {
                            char line[250];
                            strcpy(line, user);
                            strcat(line, " ");
                            strcat(line, word);
                            strcat(line, "\n");
                            fileArray[count] = malloc(sizeof(char) * strlen(line) + 1);
                            strcpy(fileArray[count++], line);
                        }
                        else if (strcmp(user, username) == 0)
                        {
                            removed = 1;
                        }
                        user[0] = 0;
                    }
                }

                /* closes file and reopens it as write */
                fclose(f);

                f = fopen(streamUsers, "w");

                /* prints to file while at the same time freeing array */
                int i;
                for (i = 0; i < count; i++)
                {
                    fprintf(f, "%s", fileArray[i]);
                    free(fileArray[i]);
                    fileArray[i] = NULL;
                }
                free(fileArray);
                fileArray = NULL;

                fclose(f);
                if (removed == 1)
                    printf("Succesfuly removed %s from %s<br>", username, stream);
                else
                    printf("Unable to find user %s, could not remove!<br>", username);
            }
            else
            {
                printf("Unable to open stream %s...skipping<br>", stream);
            }
        }
        stream = strtok(NULL, ",");
    }

    return 0;
}

int updateStream(struct userPost * st)
{
    /* fixes the new line character that gets appended to streamname causing space */
    char stream[100], streamData[70], streamUsers[70];
    int bytes = 0;
    strcpy(stream, "a2/messages/");
    strcat(stream, st->streamname);
    strcat(stream, "Stream");

    FILE * f;
    f = fopen(stream, "r");

    /* prepares stream data for when we update it later with message */
    strcpy(streamData, "a2/messages/");
    strcat(streamData, st->streamname);
    strcat(streamData, "StreamData");

    /* prepares stream users for when we check if the user has permission */
    strcpy(streamUsers, "a2/messages/");
    strcat(streamUsers, st->streamname);
    strcat(streamUsers, "StreamUsers");

    if (f == NULL)
    {
        printf("Error: stream does not exist, could not complete your operation\n");
        return 0;
    }
    else
    {
        fclose(f);

        char word[50], user[100];
        strcpy(user, "");
        char ch;
        int found = 0;

        /* check if user has permission */
        f = fopen(streamUsers, "r");
        while (fscanf(f, "%s%c", word, &ch) != EOF)
        {
            if (ch != '\n')
            {
                strcat(user, word);
                char c[2];
                c[0] = ch;
                c[1] = '\0';
                strcat(user, c);
            }
            else
            {
                user[strlen(user) - 1] = '\0';
                if (strcmp(user, st->username) == 0)
                {
                    found = 1;
                    break;
                }
                user[0] = 0;
            }
        }

        fclose(f);

        if (found == 0)
        {
            printf("Error: insufficient permissions for user: %s<br>", st->username);
            return 0;
        }
    }

    f = fopen(stream, "a");

    /* updates stream */
    fprintf(f, "Sender: %s\n", st->username);
    fprintf(f, "Date: %s\n", st->date);
    char text[3000];
    strcpy(text, st->text);
    if (st->text[strlen(st->text) - 1] != '\n')
    {
        strcat(text, "\n");
    }
    fprintf(f, "%s", text);

    fclose(f);

    f = fopen(stream, "r");
    /* counts lines */
    int temp;

     temp = fgetc(f);
     while(temp != EOF)
     {
         bytes++;
         temp = fgetc(f);
     }

    fclose(f);

    /* updates streamData */
    f = fopen(streamData, "a");
    fprintf(f, "%d\n", bytes);
    fclose(f);

    printf("Succesfuly posted the message!<br>");

    return 0;
}
