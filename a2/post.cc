#include "stream.h"
#include <time.h>
#include <stdio.h>

class PostEntry {
    struct userPost * formatEntry(char * sender, char * stream, char * date, char * text){
        struct userPost * post;
        post = malloc(sizeof(struct userPost));
        if (post != NULL)
        {
            post->streamname = malloc(sizeof(char) * strlen(stream) + 1);
            post->username = malloc(sizeof(char) * strlen(sender) + 1);
            post->date = malloc(sizeof(char) * strlen(date) + 1);
            post->text = malloc(sizeof(char) * strlen(text) + 1);

            if (post->streamname == NULL)
            {
                printf("Failed to allocate space for streamname\n");
                printf("</body>\n");
                printf("</html>\n");
                free(post->streamname);
                free(post);
                exit(1);
            }

            if (post->username == NULL)
            {
                printf("Failed to allocate space for username\n");
                printf("</body>\n");
                printf("</html>\n");
                free(post->username);
                free(post->streamname);
                free(post);
                exit(1);
            }

            if (post->date == NULL)
            {
                printf("Failed to allocate space for date\n");
                printf("</body>\n");
                printf("</html>\n");
                free(post->date);
                free(post->username);
                free(post->streamname);
                free(post);
                exit(1);
            }

            if (post->text == NULL)
            {
                printf("Failed to allocate space for date\n");
                printf("</body>\n");
                printf("</html>\n");
                free(post->text);
                free(post->date);
                free(post->username);
                free(post->streamname);
                free(post);
                exit(1);
            }

            strcpy(post->streamname, stream);
            strcpy(post->username, sender);
            strcpy(post->date, date);
            strcpy(post->text, text);
        }
        else
        {
            printf("Failed to allocate space for post\n");
            printf("</body>\n");
            printf("</html>\n");
            free(post);
            exit(1);
        }
        return(post);
    }

    void getTimeDate(char * currentTime){
        time_t t;
        t = time(NULL);
        struct tm time = *localtime(&t);
        char timeSuffix[50];
        char * months[12] = {"Jan", "Feb", "Mar", "Apr", "May",
        "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
        int hour;

        if (time.tm_hour > 12)
        {
            hour = time.tm_hour - 12;
            strcpy(timeSuffix, "PM");
        }
        else
        {
            if (time.tm_hour == 0)
            {
                hour = time.tm_hour + 12;
            }
            else
            {
                hour = time.tm_hour;
            }
            strcpy(timeSuffix, "AM");
        }

        sprintf(currentTime, "%s. %d, %d %d:%02d %s", months[time.tm_mon], time.tm_mday, time.tm_year + 1900, hour, time.tm_min, timeSuffix);

    }

    void submitPost(struct userPost * p){
        updateStream(p);
    }

    void freePost(struct userPost * p){
        free(p->streamname);
        free(p->username);
        free(p->date);
        free(p->text);
        free(p);
    }
}

int main(int argc, char *argv[]) {
    if (argc == 1)
    {
        printf("Please enter a sender as a parameter!\n");
        printf("</body>\n");
        printf("</html>\n");
        exit(1);
    }

    /* copies the sender data */
    char sender[200];
    char currentTime[100];
    char stream[100];
    char text[2000];
    struct userPost * post;

    strcpy(sender, "");
    strcpy(stream, argv[1]);

    int i;
    for (i = 2; i < argc; i++)
    {
        strcat(sender, argv[i]);
        if (i + 1 != argc)
        {
            strcat(sender, " ");
        }
    }

    FILE * f = fopen("temp.txt", "r");
    if (f == NULL)
    {
        printf("failed to open file exiting...\n");
        exit(1);
    }
    char c;
    i = 0;
    while((c = fgetc(f)) != EOF)
    {
        text[i++] = c;
    }
    text[i] = '\0';
    fclose(f);
    remove("temp.txt");

    class PostEntry myPostEntry;
    myPostEntry.getTimeDate(currentTime);
    post = myPostEntry.formatEntry(sender, stream, currentTime, text);
    myPostEntry.submitPost(post);
    myPostEntry.freePost(post);
    printf("</body>\n");
    printf("</html>\n");
    return 0;
}
