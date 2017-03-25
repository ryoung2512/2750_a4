#ifndef _PARSER_H_
#define _PARSER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "commands.h"

/**
 * chooseType
 * Takes in different types of html possibilities and chooses appropriate function.
 * @param  characteristics  Array of characteristics to do with html item
 * @param  position         length of characteristics
 * @param  arguments        Used for login
 * @param  args             Length of arguments
 */
void chooseType(char type, char ** characteristics, int position, char ** arguments, int args);

/**
 * freeArrayElements
 * Frees the array elements of a 2d char array
 * @param  characteristics  Array
 * @param  position         length of characteristics
 */
void freeArrayElements(char ** characteristics, int position);

/**
 * readFile
 * Reads the file and parses it
 * @param  input            The file
 * @param  filename         The filename
 * @param  arguments        Used for login
 * @param  args             Length of arguments
 */
void readFile(FILE * input, char * filename, char ** arguments, int args);

#endif
