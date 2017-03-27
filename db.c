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
void performAction(char * flag, MYSQL * con, char const *argv[]);

void checkArgs(int argc)
{
    if (argc < 2)
    {
        printf("error: please make sure you have at least one argument: ./db -clear\n");
        exit(1);
    }
}

/* standard error message from his example */
void error(char * msg, MYSQL * con)
{
    printf("%s\n%s\n", msg, mysql_error(con));
    exit(1);
}

void performAction(char * flag, MYSQL * con, char const *argv[])
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
    else if (strcmp(flag, "-updateR") == 0)
    {
        char username[80], stream[80], value[40], q[200];
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        strcpy(value, argv[4]);

        sprintf(q, "UPDATE users SET msg_read=%d WHERE name='%s' and stream='%s' and msg_read < %d", atoi(value), username, stream, atoi(value));
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Failed to update users");
            error(err, con);
        }

    }
    else if (strcmp(flag, "-fetchP") == 0)
    {
        char q[200], username[80], stream[80], count[40], limit[40];
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        strcpy(count, argv[4]);
        strcpy(limit, argv[5]);
        if (strcmp(stream, "all") == 0)
        {
            char a[200];
            sprintf(a, "SELECT * FROM users WHERE name='%s'", username);
            if(mysql_query(con,a))
            {
                char err[80];
                sprintf(err, "Could not fetch users from %s", tables[0]);
                error(err, con);
            }
            result = mysql_store_result(con);
            if (!result) error("Failed to store result", con);
            int rows = mysql_num_rows(result);
            i = 0;
            sprintf(q, "SELECT * FROM posts WHERE ");
            while((row = mysql_fetch_row(result)))
            {
                char temp[40];
                sprintf(temp, " stream='%s'", row[1]);
                strcat(q, temp);
                if (i + 1 < rows)
                    strcat(q, " or ");
                i++;
            }
            char lim[40];
            sprintf(lim, " LIMIT %d,%d", atoi(count), atoi(limit));
            strcat(q, lim);
        }
        else
            sprintf(q, "SELECT * FROM posts WHERE stream='%s' LIMIT %d,%d", stream, atoi(count) , atoi(limit));
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch users from %s", tables[0]);
            error(err, con);
        }
        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);
        int rows = mysql_num_rows(result);
        if (rows > 0)
        {
            while((row = mysql_fetch_row(result)))
            {
                printf("Sender: %s\n", row[0]);
                printf("Date: %s\n", row[1]);
                printf("Message: %s\n", row[2]);
                printf("%s\n", row[3]);
            }
        }
    }
    else if (strcmp(flag, "-getRead") == 0)
    {
        char username[80], stream[80], q[200];
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        if (strcmp(stream, "all") == 0)
            sprintf(q, "SELECT * FROM users WHERE name='%s'", username);
        else
            sprintf(q, "SELECT * FROM users WHERE name='%s' and stream='%s'", username, stream);
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch users from %s", tables[0]);
            error(err, con);
        }
        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);
        int rows = mysql_num_rows(result);
        if (rows == 0)
        {
            printf("0");
        }
        else
        {
            int count = 0;
            while((row = mysql_fetch_row(result)))
            {
                count += atoi(row[2]);
            }
            printf("%d", count);
        }
    }
    else if (strcmp(flag, "-lPosts") == 0)
    {
        char username[80], stream[80], limit[30], q[200], a[200];
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        strcpy(limit, argv[4]);

        int l = atoi(limit);
        if (strcmp(stream, "all") == 0)
        {
            sprintf(a, "SELECT * FROM users WHERE name='%s'", username);
            if(mysql_query(con,a))
            {
                char err[80];
                sprintf(err, "Could not fetch users from %s", tables[0]);
                error(err, con);
            }
            result = mysql_store_result(con);
            if (!result) error("Failed to store result", con);
            int rows = mysql_num_rows(result);
            i = 0;
            sprintf(q, "SELECT * FROM posts WHERE ");
            while((row = mysql_fetch_row(result)))
            {
                char temp[40];
                sprintf(temp, " stream='%s'", row[1]);
                strcat(q, temp);
                if (i + 1 < rows)
                    strcat(q, " or ");
                i++;
            }
            char lim[40];
            sprintf(lim, " LIMIT %d", l);
            strcat(q, lim);
        }
        else
        {
            sprintf(q, "SELECT * FROM posts WHERE stream='%s' LIMIT %d", stream, l);
        }

        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch users from %s", tables[0]);
            error(err, con);
        }
        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);
        while((row = mysql_fetch_row(result)))
        {
            printf("Stream: %s\n", row[3]);
            printf("Sender: %s\n", row[0]);
            printf("Date: %s\n", row[1]);
            printf("Message: %s\n", row[2]);
        }
    }
    else if (strcmp(flag, "-pCount") == 0)
    {
        char username[80], stream[80], q[80];
        int count = 0;
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        if (strcmp(stream, "all") == 0)
        {
            sprintf(q, "SELECT * FROM users WHERE name='%s'", username);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not fetch users from %s", tables[0]);
                error(err, con);
            }

            result = mysql_store_result(con);
            if (!result) error("Failed to store result", con);

            while((row = mysql_fetch_row(result)))
            {
                sprintf(q, "SELECT * FROM posts WHERE stream='%s'", row[1]);
                if(mysql_query(con,q))
                {
                    char err[80];
                    sprintf(err, "Could not fetch posts from posts");
                    error(err, con);
                }
                MYSQL_RES * r = mysql_store_result(con);
                if (!r) error("Failed to store result", con);

                int rows = mysql_num_rows(r);
                count += rows;
            }
        }
        else
        {
            sprintf(q, "SELECT * FROM posts WHERE stream='%s'", stream);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not fetch posts from posts");
                error(err, con);
            }
            result = mysql_store_result(con);
            if (!result) error("Failed to store result", con);

            int rows = mysql_num_rows(result);
            count += rows;
        }
        printf("%d", count);
    }
    else if (strcmp(flag, "-lStreams") == 0)
    {
        char username[80], q[80];
        strcpy(username, argv[2]);
        sprintf(q, "SELECT * FROM users WHERE name='%s'", username);
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Error: users does not exist could not complete your operation");
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);

        int rows = mysql_num_rows(result);
        if (rows == 0)
        {
            printf("Sorry unable to find any groups for %s. Please add some using addauthor!\n", username);
        }
        else
        {
            printf("<form action=\"viewer.php\" method=\"post\">\n");
            int first = 0;
            while((row = mysql_fetch_row(result)))
            {
                if (first == 0)
                {
                    printf("%s: <input type=\"radio\" checked=\"checked\" name=\"stream\" value=\"%s\"/><br>\n", row[1], row[1]);
                    first = 1;
                }
                else
                {
                    printf("%s: <input type=\"radio\" name=\"stream\" value=\"%s\"/><br>\n", row[1], row[1]);
                }
            }
            printf("all: <input type=\"radio\" name=\"stream\" value=\"all\"/><br>\n");
            printf("<input type=\"hidden\" name=\"username\" value=\"%s\"/>\n", username);
            printf("<input type=\"hidden\" name=\"counter\" value=\"0\"/>\n");
            printf("<input type=\"hidden\" name=\"sorted\" value=\"0\"/>\n");
            printf("<input type=\"hidden\" name=\"name\" value=\"choose\"/>\n");
            printf("<input type=\"submit\" value=\"choose\"/>\n");
            printf("</form>\n");
        }

    }
    else if (strcmp(flag, "-post") == 0)
    {
        char q[2000];
        char username[80];
        char stream[80];
        char date[80];
        char message[1000];

        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        strcpy(date, argv[4]);
        strcpy(message, argv[5]);

        sprintf(q, "SELECT * from users WHERE name='%s' and stream='%s'", username, stream);
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Error: stream does not exist could not complete your operation");
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);

        int rows = mysql_num_rows(result);
        if (rows == 0)
        {
            printf("Error you do not have permission to post to that stream\n");
        }
        else
        {
            sprintf(q, "insert into posts values('%s', '%s', '%s', '%s')", username, date, message , stream);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Failed to insert post");
                error(err, con);
            }
            printf("The post has been submitted!\n");
        }
    }
    else if (strcmp(flag, "-addauthor") == 0)
    {
        char q[80];
        char username[80];
        char stream[80];
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);
        char * create[] = {
            "create table if not exists users (name varchar(40), stream varchar(200), msg_read int)",
            "create table if not exists posts (name varchar(40), date varchar(40), message varchar(255), stream varchar(40))",
            "create table if not exists streams (name varchar(40))"  };

        for (i = 0; i < 3; i++)
        {
            if(mysql_query(con,create[i]))
            {
                char err[80];
                sprintf(err, "Could not create table");
                error(err, con);
            }
        }

        sprintf(q, "SELECT * FROM streams WHERE name='%s'", stream);
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch streams");
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result)
            error("Failed to store result", con);

        int rows = mysql_num_rows(result);
        if (rows == 0)
        {
            sprintf(q, "insert into streams values('%s')", stream);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not fetch streams");
                error(err, con);
            }
        }

        /* make username a actual var */
        sprintf(q, "SELECT * FROM users WHERE name='%s' and stream='%s'", username, stream);
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch User");
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);

        rows = mysql_num_rows(result);
        if (rows == 0)
        {
            sprintf(q, "insert into users values ('%s', '%s', 0)", username, stream);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not give user permission");
                error(err, con);
            }
            printf("%s was succesfuly added to %s\n", username, stream);
        }
        else
        {
            printf("error: %s already in %s\n", username, stream);
        }

    }
    else if (strcmp(flag, "-removeA") == 0)
    {
        char username[80];
        char stream[80];
        char q[200];
        strcpy(username, argv[2]);
        strcpy(stream, argv[3]);

        sprintf(q, "SELECT * FROM users WHERE name='%s' and stream='%s'", username, stream);
        if(mysql_query(con,q))
        {
            char err[80];
            sprintf(err, "Could not fetch User");
            error(err, con);
        }

        result = mysql_store_result(con);
        if (!result) error("Failed to store result", con);

        int rows = mysql_num_rows(result);
        if (rows == 0)
            printf("Error: could not remove %s from %s because no record exists\n", username, stream);
        else
        {
            sprintf(q, "DELETE FROM users WHERE name='%s' and stream='%s'", username, stream);
            if(mysql_query(con,q))
            {
                char err[80];
                sprintf(err, "Could not delete User");
                error(err, con);
            }
            printf("%s was removed succesfuly from %s\n", username, stream);
        }

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

    char action[50];
    strcpy(action, argv[1]);
    performAction(action, &connection, argv);

    mysql_close(&connection);

    return 0;
}
