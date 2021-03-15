/**
 * Functions related to reading files!
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "file_utils.h"
#include "word_info.h"

/**
 * Read the file with the words and their info, and return the number of the words of 
 * this file.
 */
int read_info_file(char* path, WordInfo info_list[]) {
    FILE* fd = fopen(path, "r");

    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fd) != NULL) {
        
        char* ptr = line;
        
        char* word = strsep(&ptr, "\t");
        char* definition = strsep(&ptr, "\t");
        char pos = ptr[0];
        
        create_word_info(&info_list[count], word, definition, pos);
        count++;
    }
    fclose(fd);
    
    return count;
}

/**
 * Read the file with the words to search at the dictionary and write this at the array passed as parameter, 
 * and return the number of the words of this file.
 */
int read_query_file(char* path, char* query_list[]) {
    
    FILE* fd = fopen(path, "r");
    int count = 0;
    char line[MAX_LINE_LENGTH];
    while (fgets(line, MAX_LINE_LENGTH, fd) != NULL) {
        
        char* word = (char*) malloc(sizeof(MAX_WORD_LENGTH));
        int result = sscanf(line, "%s\n", word);
        if (result != EOF && result == 1) {
            query_list[count] = word;
            count++;
        } else {
            free(word);
        }
    }
    fclose(fd);
    
    return count;
}
