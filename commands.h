#ifndef _COMMANDS_H_
#define _COMMANDS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

void addAuthor(char ** characteristics, int position, char ** arguments, int args);

/**
 * button
 * Creates a button in html
 * @param  characteristics  Array of characteristics to do with button
 * @param  position         length of characteristics
 * @param  arguments        Used for login
 * @param  args             Length of arguments
 */
void button(char ** characteristics, int position, char ** arguments, int args);

void createPost(char ** characteristics, int position, char ** arguments, int args);

/**
 * concatenateArgs
 * Concatenates arguments together and stores the appropriate args in the appropriate variables
 * @param  arguments         The arguments
 * @param  args              The length of arguments
 * @param  username          The username of the user
 * @param  stream            The stream of the user
 * @param  counter           The current post that they are on
 * @param  limit             The maximum number of posts they can view
 * @param  sorted            Wether it is sorted by name or by date
 */
void concatenateArgs(char ** arguments, int args, char * username, char * stream, char * counter, char * limit, char * sorted);

/**
 * endFile
 * Ends the file by printing out closing html tags
 */
void endFile();

/**
 * execute
 * Executes the command, first checking current directory then a bin then /bin to see where it is
 * @param  characteristics  Array of characteristics to do with the execution
 * @param  position         length of characteristics
 */
void execute(char ** characteristics, int position);

/**
 * header
 * Creates a header in html
 * @param  characteristics  Array of characteristics to do with header
 * @param  position         length of characteristics
 */
void header(char ** characteristics, int position);

/**
 * image
 * Creates a image in html
 * @param  characteristics  Array of characteristics to do with the image
 * @param  position         length of characteristics
 */
void image(char ** characteristics, int position);

/**
 * input
 * Creates a input field in html
 * @param  characteristics  Array of characteristics to do with the input field
 * @param  position         length of characteristics
 * @param  arguments        Used for login
 * @param  args             Length of arguments
 */
void input(char ** characteristics, int position, char ** arguments, int args);

/**
 * html_link
 * Creates a link in html
 * @param  characteristics  Array of characteristics to do with the link
 * @param  position         length of characteristics
 */
void html_link(char ** characteristics, int position);

/**
 * radio
 * Creates a radio in html
 * @param  characteristics  Array of characteristics to do with the radio
 * @param  position         length of characteristics
 */
void radio(char ** characteristics, int position);

void startFile(char * title);

/**
 * text
 * Creates text in html (not really just outputs)
 * @param  characteristics  Array of characteristics to do with text
 * @param  position         length of characteristics
 */
void text(char ** characteristics, int position);

/**
 * textArea
 * Creates a textArea in html
 * @param  characteristics  Array of characteristics to do with textArea
 * @param  position         length of characteristics
 */
void textArea(char ** characteristics, int position);

#endif
