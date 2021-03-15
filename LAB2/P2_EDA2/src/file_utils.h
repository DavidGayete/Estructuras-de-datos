/**
 * Functions related with read files
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#ifndef UTIL_H
#define UTIL_H

#include "word_info.h"

#define MAX_LINES 100
#define MAX_LINE_LENGTH 100

int read_info_file(char* path, WordInfo info_list[]);
int read_query_file(char* path, char* query_list[]);

#endif
