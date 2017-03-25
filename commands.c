#include "commands.h"

void addAuthor(char ** characteristics, int position, char ** arguments, int args)
{
    char action[20], text[50], name[50], val[50], inputs[1000], id[1000], temp[50];
    strcpy(text, "");
    strcpy(name, "");
    strcpy(val, "");
    strcpy(inputs, "");
    strcpy(temp, "");
    strcpy(id, "");
    int i;
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if(strcmp(tag, "header") == 0)
        {
            char header[60];
            memcpy(header, &value[1], strlen(value) - 2);
            header[strlen(value) - 2] = '\0';
            printf("<h4>%s</h4>\n", header);
        }
        else if (strcmp(tag, "action") == 0)
        {
            strcpy(action, value);
        }
        else if (strcmp(tag, "text") == 0)
        {
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
        }
        else if (strcmp(tag, "name") == 0)
        {
            strcpy(name, value);
            memcpy(temp, &name[1], strlen(name) - 2);
            temp[strlen(name) - 2] = '\0';
        }
        else if (strcmp(tag, "value") == 0)
        {
            strcpy(val, value);
        }

        if (strlen(text) != 0 && strlen(name) != 0 && strlen(val) != 0)
        {
            char tempS[200];
            sprintf(tempS, "%s: <input style=\"margin-bottom: 10px;\"type=\"text\" name=%s value=%s/><br>\n", text, name, val);
            strcat(inputs, tempS);
            strcat(id, temp);
            strcpy(name, "");
            strcpy(val, "");
            strcpy(temp, "");
            memset(text, 0, strlen(text));
        }
    }
    printf("<form action=%s id=\"%s\" method=\"post\">\n", action, id);
    printf("%s", inputs);
    if (arguments != NULL)
    {
        char username[50], stream[50], counter[50], limit[50], sorted[50];
        concatenateArgs(arguments, args, username, stream, counter, limit, sorted);
        printf("<input type=\"hidden\" name=\"username\" value=\"%s\"/>", username);
        if (args >= 5) /* if logged in */
        {
            printf("<input type=\"hidden\" name=\"stream\" value=\"%s\"/>", stream);
            printf("<input type=\"hidden\" name=\"counter\" value=\"%s\"/>", counter);
            printf("<input type=\"hidden\" name=\"limit\" value=\"%s\"/>", limit);
            printf("<input type=\"hidden\" name=\"sorted\" value=\"%s\"/>", sorted);
        }
    }
    printf("<input type=\"hidden\" name=\"name\" value=\"%s\"/>\n", id);
    printf("<input type=\"submit\" value=\"submit\"/>\n");
    printf("</form>\n");
}

void button(char ** characteristics, int position, char ** arguments, int args)
{
    int i;
    char link[200], name[200], extraParams[200];
    strcpy(name, "");
    strcpy(link, "");
    strcpy(extraParams, "");
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");
        if (strcmp(tag, "name") == 0)
        {
            strcpy(name, value);
        }
        else if (strcmp(tag, "link") == 0)
        {
            strcpy(link, value);
        }
        else
        {
            strcat(extraParams, " ");
            strcat(extraParams,characteristics[i]);
        }
    }
    printf("<form action=%s method=\"post\" style=\"display: inline; margin-left: 4%%;\">\n", link);
    if (arguments != NULL)
    {
        char username[50], stream[50], counter[50], limit[50], sorted[50];
        concatenateArgs(arguments, args, username, stream, counter, limit, sorted);
        printf("<input type=\"hidden\" name=\"username\" value=\"%s\"/>", username);
        if (args >= 5) /* if logged in */
        {
            printf("<input type=\"hidden\" name=\"stream\" value=\"%s\"/>", stream);
            printf("<input type=\"hidden\" name=\"counter\" value=\"%s\"/>", counter);
            printf("<input type=\"hidden\" name=\"limit\" value=\"%s\"/>", limit);
            printf("<input type=\"hidden\" name=\"sorted\" value=\"%s\"/>", sorted);
        }
    }
    printf("<input type=\"hidden\" name=\"name\" value=%s/>\n", name);
    printf("<input type=\"submit\" name=%s value=%s%s/>\n", name, name, extraParams);
    printf("</form>\n");
}


void concatenateArgs(char ** arguments, int args, char * username, char * stream, char * counter, char * limit, char * sorted)
{
    /* stores arguments in appropriate spots */
    if (args >= 5)
    {
        int i;
        strcpy(username, "");
        for (i = 0; i < args - 4; i++)
        {
            strcat(username, arguments[i]);
            if (i + 1 != args - 4)
                strcat(username, " ");
        }
        strcpy(stream, arguments[i++]);
        strcpy(counter, arguments[i++]);
        strcpy(limit, arguments[i++]);
        strcpy(sorted, arguments[i]);
    }
    else
    {
        strcpy(username, "");
        int i;
        for (i = 0; i < args; i++)
        {
            strcat(username, arguments[i]);
            if (i + 1 != args)
                strcat(username, " ");
        }
    }
}

void createPost(char ** characteristics, int position, char ** arguments, int args)
{
    char action[20], text[50], name[50], val[50], inputs[1000], id[1000], temp[50];
    strcpy(text, "");
    strcpy(name, "");
    strcpy(val, "");
    strcpy(inputs, "");
    strcpy(temp, "");
    strcpy(id, "");
    int i;
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if(strcmp(tag, "header") == 0)
        {
            char header[60];
            memcpy(header, &value[1], strlen(value) - 2);
            header[strlen(value) - 2] = '\0';
            printf("<h4>%s</h4>\n", header);
        }
        else if (strcmp(tag, "action") == 0)
        {
            strcpy(action, value);
        }
        else if (strcmp(tag, "text") == 0)
        {
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
        }
        else if (strcmp(tag, "name") == 0)
        {
            strcpy(name, value);
            memcpy(temp, &name[1], strlen(name) - 2);
            temp[strlen(name) - 2] = '\0';
        }
        else if (strcmp(tag, "value") == 0)
        {
            strcpy(val, value);
        }

        if (strlen(text) != 0 && strlen(name) != 0 && strlen(val) != 0)
        {
            char tempS[200];
            sprintf(tempS, "%s: <input style=\"margin-bottom: 10px;\"type=\"text\" name=%s value=%s/><br>\n", text, name, val);
            strcat(inputs, tempS);
            strcat(id, temp);
            strcpy(name, "");
            strcpy(val, "");
            strcpy(temp, "");
            memset(text, 0, strlen(text));
        }
    }
    printf("<form action=%s id=\"%s\" method=\"post\">\n", action, id);
    printf("%s", inputs);
    if (arguments != NULL)
    {
        char username[50], stream[50], counter[50], limit[50], sorted[50];
        concatenateArgs(arguments, args, username, stream, counter, limit, sorted);
        printf("<input type=\"hidden\" name=\"username\" value=\"%s\"/>", username);
        if (args >= 5) /* if logged in */
        {
            printf("<input type=\"hidden\" name=\"stream\" value=\"%s\"/>", stream);
            printf("<input type=\"hidden\" name=\"counter\" value=\"%s\"/>", counter);
            printf("<input type=\"hidden\" name=\"limit\" value=\"%s\"/>", limit);
            printf("<input type=\"hidden\" name=\"sorted\" value=\"%s\"/>", sorted);
        }
    }
    printf("<input type=\"hidden\" name=\"name\" value=\"%s\"/>\n", id);
    printf("<input type=\"submit\" value=\"submit\"/>\n");
    printf("</form>\n");
}

void endFile()
{
    printf("</body>\n");
    printf("</html>\n");
}

void execute(char ** characteristics, int position)
{
    int i;
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if (strcmp(tag, "exe") == 0)
        {
            char temp[50];
            memcpy(temp, &value[1], strlen(value) - 2);
            temp[strlen(value) - 2] = '\0';

            char command[70];
            strcpy(command, "./");
            strcat(command, temp);

            /* current directory */
            if (access(temp, F_OK) != -1)
            {
                system(command);
            }
            else
            {
                /* bin directory */
                char localBin[100];
                strcpy(localBin, "bin/");
                strcat(localBin, temp);
                if (access(localBin, F_OK) != -1)
                {
                    char LBCommand[200];
                    strcpy(LBCommand, "cd bin &&");
                    strcat(LBCommand, command);
                    system(LBCommand);
                }
                else
                {
                    /* system bin directory */
                    char systemBin[100];
                    strcpy(systemBin, "/bin/");
                    strcat(systemBin, temp);
                    if (access(systemBin, F_OK) != - 1)
                    {
                        char SBcommand[200];
                        strcpy(SBcommand, "cd /bin &&");
                        strcat(SBcommand, command);
                        system(SBcommand);
                    }
                    else
                    {
                        printf("executable not found<br>\n");
                    }
                }
            }
        }
    }
}

void header(char ** characteristics, int position)
{
    int size = 3, i, setText = 0;
    char text[200], extraParams[200];
    strcpy(text, "");
    strcpy(extraParams, "");

    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");
        if (strcmp(tag, "size") == 0)
            size = atoi(value);
        else if (strcmp(tag, "text") == 0)
        {
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
            setText = 1;
        }
        else
        {
            strcat(extraParams, " ");
            strcat(extraParams,characteristics[i]);
        }
    }

    if (setText == 0)
        strcpy(text, "HEADING");
    printf("<h%d%s>%s</h%d>\n", size, extraParams, text, size);
}

void image(char ** characteristics, int position)
{
    int i, width = 100, height = 100;
    char location[200], extraParams[200];
    strcpy(location, "");
    strcpy(extraParams, "");
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if (strcmp(tag, "image") == 0)
        {
            strcpy(location, value);
        }
        else if (strcmp(tag, "size") == 0)
        {
            char size[50];
            memcpy(size, &value[1], strlen(value) - 2);
            size[strlen(value) - 2] = '\0';
            width = atoi(strtok(size, "x"));
            height = atoi(strtok(NULL, ""));
        }
        else
        {
            strcat(extraParams, " ");
            strcat(extraParams, characteristics[i]);
        }
    }
    printf("<img src=%s height=\"%d\" width=\"%d\">\n", location, height, width);
}

void input(char ** characteristics, int position, char ** arguments, int args)
{
    char action[20], text[50], name[50], val[50], inputs[1000], id[1000], temp[50], extraParams[1000];
    strcpy(text, "");
    strcpy(name, "");
    strcpy(val, "");
    strcpy(inputs, "");
    strcpy(temp, "");
    strcpy(id, "");
    strcpy(extraParams, "");
    int i;
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if (strcmp(tag, "action") == 0)
        {
            strcpy(action, value);
        }
        else if (strcmp(tag, "text") == 0)
        {
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
        }
        else if (strcmp(tag, "name") == 0)
        {
            strcpy(name, value);
            memcpy(temp, &name[1], strlen(name) - 2);
            temp[strlen(name) - 2] = '\0';
        }
        else if (strcmp(tag, "value") == 0)
        {
            strcpy(val, value);
        }
        else
        {
            strcat(extraParams, " ");
            strcat(extraParams, characteristics[i]);
        }

        if (strlen(text) != 0 && strlen(name) != 0 && strlen(val) != 0)
        {
            char tempS[200];
            sprintf(tempS, "%s: <input style=\"margin-bottom: 10px;\"type=\"text\" name=%s value=%s%s/><br>\n", text, name, val, extraParams);
            strcat(inputs, tempS);
            strcat(id, temp);
            strcpy(name, "");
            strcpy(val, "");
            strcpy(temp, "");
            memset(text, 0, strlen(text));
        }
    }
    printf("<form action=%s id=\"%s\" method=\"post\">\n", action, id);
    printf("%s", inputs);
    if (arguments != NULL)
    {
        char username[50], stream[50], counter[50], limit[50], sorted[50];
        concatenateArgs(arguments, args, username, stream, counter, limit, sorted);
        printf("<input type=\"hidden\" name=\"username\" value=\"%s\"/>", username);
        if (args >= 5) /* if logged in */
        {
            printf("<input type=\"hidden\" name=\"stream\" value=\"%s\"/>", stream);
            printf("<input type=\"hidden\" name=\"counter\" value=\"%s\"/>", counter);
            printf("<input type=\"hidden\" name=\"limit\" value=\"%s\"/>", limit);
            printf("<input type=\"hidden\" name=\"sorted\" value=\"%s\"/>", sorted);
        }
    }
    printf("<input type=\"hidden\" name=\"name\" value=\"%s\"/>\n", id);
    printf("<input type=\"submit\" value=\"submit\"/>\n");
    printf("</form>\n");
}

void html_link(char ** characteristics, int position)
{
    char text[200], extraParams[200], link[200];
    int i, setText = 0;
    strcpy(text, "");
    strcpy(extraParams, "");
    strcpy(link, "");

    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if(strcmp(tag, "text") == 0)
        {
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
            setText = 1;
        }
        else if(strcmp(tag, "link") == 0)
        {
            strcpy(link, value);
        }
        else
        {
            strcat(extraParams, " ");
            strcat(extraParams, characteristics[i]);
        }
    }
    if (setText == 0)
        strcpy(text, "link");
    printf("<a href=%s%s>%s</a>\n", link, extraParams, text);
}

void radio(char ** characteristics, int position)
{
    char action[200], name[200], extraParams[200], choices[800];
    int i, firstFound = 0;
    strcpy(action, "");
    strcpy(name, "");
    strcpy(choices, "");
    strcpy(extraParams, "");
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if (strcmp(tag, "action") == 0)
        {
            strcpy(action, value);
        }
        else if (strcmp(tag, "name") == 0)
        {
            strcpy(name, value);
        }
        else if (strcmp(tag, "value") == 0)
        {
            char valueNoQuotes[50];
            memcpy(valueNoQuotes, &value[1], strlen(value) - 2);
            valueNoQuotes[strlen(value) - 2] = '\0';

            char temp[70];
            if (firstFound == 1)
                sprintf(temp, "%s <input type=\"radio\" name=%s value=%s%s/><br>\n", valueNoQuotes, name, value, extraParams);
            else
                sprintf(temp, "%s <input type=\"radio\" name=%s value=%s%s checked/><br>\n", valueNoQuotes, name, value, extraParams);
            strcat(choices, temp);
            memset(valueNoQuotes, 0, strlen(valueNoQuotes));
            firstFound = 1;
        }
        else
        {
            strcat(extraParams, " ");
            strcat(extraParams, characteristics[i]);
        }
    }
    printf("<form action=%s method=\"post\">\n", action);
    printf("%s", choices);
    printf("</form>\n");
}

void text(char ** characteristics, int position)
{
    int i, printed = 0;
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        /* check if file exists ? */
        if (strcmp(tag, "file") == 0)
        {
            char filename[70], line[256];
            memcpy(filename, &value[1], strlen(value) -2);
            filename[strlen(value) - 2] = '\0';
            FILE * f = fopen(filename, "r");
            while (fgets(line, 256, f))
                printf("%s", line);
            fclose(f);
            printed = 1;
        }
        else if (strcmp(tag, "text") == 0)
        {
            char text[70];
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
            printf("%s\n",text);
            printed = 1;
        }
    }
    if (printed == 0)
        printf("Default Text\n");
}

void textArea(char ** characteristics, int position)
{
    int i;
    char params[200], text[100];
    strcpy(params, "");
    for (i = 0; i < position; i++)
    {
        char current[strlen(characteristics[i] + 1)];
        strcpy(current, characteristics[i]);
        char * tag = strtok(current, "=");
        char * value = strtok(NULL, "");

        if (strcmp(tag, "text") == 0)
        {
            memcpy(text, &value[1], strlen(value) - 2);
            text[strlen(value) - 2] = '\0';
        }
        else
        {
            strcat(params, " ");
            strcat(params, characteristics[i]);
        }
    }
    printf("<textarea%s>%s</textarea>\n", params, text);
}

void startFile(char * title)
{
    printf("<html>\n");
    printf("<head>\n");
    printf("<title>%s</title>\n", title);
    printf("</head>\n");
    printf("<body>\n");
}
