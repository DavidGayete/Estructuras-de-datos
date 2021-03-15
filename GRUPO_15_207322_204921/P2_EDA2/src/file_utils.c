/**
 * Functions related with read files and treat the information.
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
 *  Read the information of data_dict.tsv and creates a WordInfo for each line in the file.
 *  All the words created ara inserted in the Array passed as parameter.
 *  Returns the number of the words read.
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
 *  Read the words of data_list.tsv and fill the array passed as parameter with these words.
 *  Returns the number of the words read.
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
