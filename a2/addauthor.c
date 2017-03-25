#include "addauthor.h"

void checkArgs(int argc)
{
    if (argc == 1)
    {
        printf("Error: Please provide a author and a stream\n");
        printf("</body>\n");
        printf("</html>");
        exit(1);
    }
}

void getStreams(char * streams)
{
    printf("list streams: ");
    fgets(streams, 100, stdin);
    if (strcmp(streams, "\n") == 0)
    {
        printf("Error: stream cannot be enter please run addauthor again!\n");
        printf("</body>\n");
        printf("</html>\n");
        exit(1);
    }
    /* removes new line character */
    streams[strlen(streams) - 1] = '\0';
}

int main(int argc, char const *argv[])
{
    checkArgs(argc);

    char streams[100];
    char author[100];
    int i;
    strcpy(author, "");

    if (strcmp(argv[1], "-r") == 0)
    {
        /* fetches the author then removes everything else */
        for (i = 2; i < argc - 1; i++)
        {
            strcat(author, argv[i]);
            if (i + 1 != argc - 1)
            {
                strcat(author, " ");
            }
        }

        strcpy(streams, argv[argc- 1]);

        /* removes the user */
        removeUser(author, streams);
    }
    else
    {
        /* fetches the author then removes everything else */
        for (i = 1; i < argc - 1; i++)
        {
            strcat(author, argv[i]);
            if (i + 1 != argc - 1)
            {
                strcat(author, " ");
            }
        }

        strcpy(streams, argv[argc- 1]);

        /* adds the user */
        addUser(author, streams);
    }

    printf("</body>\n");
    printf("</html>\n");
    return 0;
}
