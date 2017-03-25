#ifndef __ADDAUTHOR_H__
#define __ADDAUTHOR_H__

#include "stream.h"
#include <stdio.h>

/**
 * checkArgs
 * Checks if there are enough args (i.e an author) if not exists
 * printing an error message.
 * @param  argc      The number of arguements
 * @return void
 */
void checkArgs(int argc);

/**
 * getStreams
 * Gets the stream string prints an error message and exists if empty.
 * @param  streams      The stream string
 * @return void
 */
void getStreams(char * streams);

#endif
