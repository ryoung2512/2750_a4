#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/**
 * isVariableType
 * Checks if a string is a variable type.
 * @param str      The str to check.
 * @return         Is a param (yes = 1)
 */
int isVariableType(char * str);

/**
 * isPunct
 * Checks if a string is a punctuation.
 * @param str      The str to check.
 * @return         Is a punct (yes = 1)
 */
int isPunct(char * str);

/**
 * isKeyword
 * Checks if a string is a keyword.
 * @param str      The str to check.
 * @return         Is a keyword (yes = 1)
 */
int isKeyword(char * str);

/**
 * noSpace
 * Checks if a string needs a space after it,
 * @param str      The str to check.
 * @return         Is a param (yes = 1)
 */
int noSpace(char * str);

#endif
