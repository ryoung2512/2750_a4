#ifndef __A1_H__
#define __A1_H__

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "list.h"

/**
 * addWord
 * Takes a pointer to the head of the list, and a string/word to addWord
 * checks to make sure its valid then adds it.
 * Returns the head of the list after the operation is performed
 * @param  theList   Node* representing the head of the list
 * @param  word      The word you want to add.
 * @return           Node* new head of the list
 */
Node * addWord(Node * theList, char * word);

/**
 * checkFile
 * Takes a file and a filename as input, checks to see if it could
 * open the file, if it cannot then it will print an error message and
 * quit the program.
 * @param  file          The file
 * @param  fileName      The files name
 * @return               none
 */
void checkFile(FILE* file, const char * fileName);

/**
 * mainFunctions
 * Executes all the main Functions. This program is written
 * VERY procedurally so it executes all the different functionality
 * needed.
 * @param  list       Node* representing the head of the list
 * @param  fileName   The files name
 * @return            none
 */
void mainFunctions(Node * list, const char * fileName);

/**
 * parseFile
 * A crazy function that parses everything in the file. 140 lines
 * of working at 1am. It works though! Takes file as input and
 * filename.
 * @param  file          The file to parse
 * @param  fileName      The filename.
 * @return               none.
 */
void parseFile(FILE * file, const char * fileName);

#endif
