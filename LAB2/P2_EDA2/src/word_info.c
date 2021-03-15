/**
 * Functions related with the dataType WordInfo.
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#include <stdio.h>
#include <string.h>
#include "word_info.h"
#include "file_utils.h"

// Print all the information of the WordInfo passed as parameter.
void print_word_info(WordInfo wi) {
    printf("-> %s (%c): %s\n", wi.word, wi.pos, wi.definition);
}

// Returns the word of WordInfo
char* get_word(WordInfo* wi) {
    return wi->word;
}

// Create a WordInfo with the variables passed as parameter.
void create_word_info(WordInfo* wi, char* word, char* definition, char pos) {
    strcpy(wi->word, word);
    strcpy(wi->definition, definition);
    wi->pos = pos;
}
