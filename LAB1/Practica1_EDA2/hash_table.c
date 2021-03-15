/**
 * Functions related with HashTable!
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#include <stdio.h>
#include <stdlib.h>

#include "hash_table.h"
#include "sort.h"

/**
 * Check letter to letter the alphabet and it's compared with the first letter of the word passed
 * as parameter if they match, the algorithm return the position of the letter in the alphabet.  
 */
int hash_function(char* word) {
    char* abcd = "abcdefghijklmnopqrstuvwxyz";
    for (int i = 0; i < N; i++) {
        if (abcd[i] == word[0]) {
            return i;
        }
    }
    return ERROR;
}

/**
 * This function initialize the HashTable calling the function init_list for each list 
 * in the HashTable.
 */
void init_table(HashTable* table) {
    table->size = 0;
    for (int i = 0; i < N; i++) {
        init_list(&table->list[i]);
    }
}

/**
 * This function clear the table, releasing all the Nodes reserved with mallocs,
 * in the function encapsulate. For this is called the function clear_list for each
 * list of the HashTable.
 */
void clear_table(HashTable* table) {
    for (int i = 0; i < N; i++) {
        if (table->list[i].size > 0) {
            clear_list(&table->list[i]);
        }
    }
    table->size = 0;
}

/**
 * This function return the number of the Words saved in the ditionary.
 */
int size(HashTable* table) {
    int size = 0;
    for(int i=0;i<N;i++){
        size += table->list[i].size;
    }
    if(size != table->size){
        table->size = size;
    }
    return table->size;
}

/**
 * This function try to insert a WordInfo in the dictionary if the word isn't in it.
 * If the function exists_word return True, this WordInfo will not inserted on the dictionary
 * and the function return FALSE.
 * If the function exists_word return Frue, calls the function insert_into_list() and 
 * return TRUE.
 */
bool insert_word_info(HashTable* table, WordInfo wi) {
    int index = hash_function(wi.word);
    LinkedList* list = &table->list[index];
    if (!exists_word(table, wi.word)) {
        int result = insert_into_list(list, wi);
        if (result == SUCCESS) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * This function checks if the word passed as parameter exist in the dictionary.
 * Calls the hash_function to know in which list need to search, and after check if
 * this word exist in the correct list.
 * If exist return TRUE, else return FALSE.
 */
bool exists_word(HashTable* table, char* word) {
    int d = hash_function(word);
    int respuesta = buscar_lista(&table->list[d], word);
    if (respuesta == TRUE) {
        return TRUE;
    }
    return FALSE;
}

/**
 * Call the function buscar_lista, if return TRUE call the function delete_from_list()
 * and if the result is SUCCESS return True.
 * If the function buscar_lista return FALSE, delete_word() return FALSE.
 */
bool delete_word(HashTable* table, char* word) {
    int d = hash_function(word);
    int respuesta = buscar_lista(&table->list[d], word);
    if (respuesta == TRUE) {
        int result = delete_from_list(&table->list[d], word);
        if (result == SUCCESS) {
            return TRUE;
        }
    }
    return FALSE;
}

/**
 * This function calls buscar_lista() if returns TRUE, go through the list until 
 * match with the word, and return the pointer of this WordInfo.
 * If buscar_lista() return FALSE, the function return a NULL pointer.
 */
WordInfo* find_word(HashTable* table, char* word) {
    int d = hash_function(word);
    int respuesta = buscar_lista(&table->list[d], word);
    if (respuesta == TRUE) {
        Node* enode = table->list[d].start;
        while (enode != NULL) {
            if (strcmp(word, enode->data.word) == 0) {
                return &enode->data;
            }
            enode = enode->next;
        }
    }
    return NULL;
}

/**
 * This function first check the size of the HashTable, create a String Array with
 * and fill it with the words of the dictionary.
 * After with the sort() function, the StringArray is sorted with a insertion algorithm
 * and the function print each step of the sort algorithm.
 * Finally in the last step the dictionary is printed alphabetically.
 */
void print_sorted_word_info(HashTable* table) {
    int maxSize = size(table);
    char *tosort[maxSize];
    vectoritzar(&tosort, table);
    sort(&tosort, maxSize);
}
