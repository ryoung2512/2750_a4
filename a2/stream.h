#ifndef __STREAM_H__
#define __STREAM_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct userPost
{
    char * username;
    char * streamname;
    char * date;
    char * text;
};

/**
 * addUser
 * Adds the username to each stream given in list. Prints
 * an error message and skips if it already contains the name.
 * @param  username      The username.
 * @param  list          The list of streams.
 * @return int
 */
int addUser(char * username, char * list);

/**
 * removeUser
 * Removes the username from each stream given in list. If
 * a stream doesn't exist it skips over it printing out a
 * message.
 * @param  username      The username.
 * @param  list          The list of streams.
 * @return int
 */
int removeUser(char * username, char * list);

/**
 * updateStream
 * Updates the stream given in the struct and performs
 * the appropriate actions to add it to the file.
 * @param  st      The struct
 * @return int
 */
int updateStream(struct userPost * st);

#endif
