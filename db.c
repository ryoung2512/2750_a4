#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <mysql/mysql.h>

#define HOST "dursley.socs.uoguelph.ca"
#define USER "ryoung08"
#define PWD  "0925398"
#define DB "ryoung08"

void checkArgs(int argc);
void error(char * msg, MYSQL * con);
void performAction(char * flag, MYSQL * con);

void checkArgs(int argc)
{
    if (argc < 2)
    {
        printf("error: please only use 1 argument such as: ./db -clear\n");
        exit(1);
    }
}

/* standard error message from his example */
void error(char * msg, MYSQL * con)
{
    printf("%s\n%s\n", msg, mysql_error(con));
    exit(1);
}

void performAction(char * flag, MYSQL * con)
{
    MYSQL_RES * result;
    MYSQL_ROW row;
    MYSQL_FIELD * field;

    int i;
    char * tables[] = {"users", "posts", "streams"};

    if (strcmp(flag, "-clear") == 0)
    {
        for (i = 0; i < 3; i++)
        {
            char q[80];
            sprintf(q, "TRUNCATE TABLE %s", tables[i]);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not empty table %s", tables[i]);
                error(err, con);
            }
        }
        printf("Tables have been cleared\n");
    }
    else if (strcmp(flag, "-reset") == 0)
    {
        for (i = 0; i < 3; i++)
        {
            char q[80];
            sprintf(q, "DROP TABLE %s", tables[i]);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not drop table %s", tables[i]);
                error(err, con);
            }
        }
        printf("Tables have been dropped\n");
    }
    else if (strcmp(flag, "-posts") == 0)
    {
        char q[80];
        sprintf(q, "SELECT * FROM %s", tables[1]);

        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch users from %s", tables[0]);
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result)
            error("Failed to store result", con);

        while((row = mysql_fetch_row(result)))
        {
            printf("Stream: %s\n", row[3]);
            printf("Sender: %s\n", row[0]);
            printf("Date: %s\n", row[1]);
            printf("Message: %s\n", row[2]);
        }
    }
    else if (strcmp(flag, "-users") == 0)
    {
        char q[80];
        sprintf(q, "SELECT * FROM %s", tables[0]);

        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch users from %s", tables[0]);
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result)
            error("Failed to store result", con);

        int rows = mysql_num_rows(result);
        if (rows == 0)
            printf("There are no users to display\n");
        else
            while((row = mysql_fetch_row(result))) printf("%s\n", row[0]);

    }
    else if (strcmp(flag, "-streams") == 0)
    {
        char q[80];
        sprintf(q, "SELECT * FROM %s", tables[2]);

        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch users from %s", tables[0]);
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result)
            error("Failed to store result", con);

        int rows = mysql_num_rows(result);
        if (rows == 0)
            printf("There are no streams to display\n");
        else
            while((row = mysql_fetch_row(result))) printf("%s\n", row[0]);
    }
    else if (strcmp(flag, "-help") == 0)
    {
        printf("Help:\n");
        printf("------\n");
        printf("-clear: empties the tables\n");
        printf("-reset: deletes the tables\n");
        printf("-posts: prints out all the posts\n");
        printf("-users: prints out all the users");
        printf("-streams: prints out all the streams\n");

    }
    else
    {
        printf("Sorry, that isn't a valid command. If you need help with the commands please type -help as your agument\n");
    }
}

int main(int argc, char const *argv[]) {
    checkArgs(argc);

    MYSQL connection;

    mysql_init(&connection);
    mysql_options(&connection, MYSQL_READ_DEFAULT_GROUP, "ryoung08");

    if (!mysql_real_connect(&connection, HOST, USER, PWD, DB, 0, NULL, 0))
    {
        char err[250];
        sprintf(err, "Error: unable to connect to %s", HOST);
        error(err, &connection);
    }
    printf("Connected succesfuly to %s\n", HOST);

    char action[50];
    strcpy(action, argv[1]);
    performAction(action, &connection);

    mysql_close(&connection);
    printf("Closed connection\n");

    return 0;
}
