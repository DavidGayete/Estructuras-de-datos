/**
 * Functions related with the struct LinkedList and Node!
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "commons.h"
#include "linked_list.h"
#include "hash_table.h"


/*this function initialize a linked list done in the main. It puts the linkedList size on 0, and the pointers on NULL*/
void init_list(LinkedList* l) {
    l->size = 0;
    l->last = NULL;
    l->start = NULL;
}
/*is called by clear_table and his function is to clear the list done */
void clear_list(LinkedList* l) {
    Node* enode = l->last;
    Node* enodeAux;
    if(enode->prev != NULL){
        enodeAux = enode->prev;
    }
    while (l->size > 1) {
        free(enode);
        enode = enodeAux;
        enodeAux = enode->prev;
        l->size--;
    }
    if (l->size == 1) {
        free(enode);
        l->start = NULL;
        l->last = NULL;
        l->size = 0;
    }
}

/**
 * Call the function encapsulateWordInfo, the node returned is added at the list modifying
 * they parameters with this new node and return SUCCESS.
 * If node is NULL return ERROR.
 */
int insert_into_list(LinkedList* l, WordInfo wi) {
    Node* node = encapsulateWordInfo(l, wi);
    if (node == NULL) {
        return ERROR;
    }
    if (l->size == 0) {
        l->start = node;
        l->last = node;
        l->size++;
    } else {
        l->last->next = node;
        l->last = node;
        l->size++;
    }
    return SUCCESS;
}

/* given a word, he looks for the word in the linkedlist, if its founded, it returns all the node,obviously,if in doesnt exist, he returns NULL*/
WordInfo* find_first_in_list(LinkedList* l, char* word) {
    if (l->size == 0) {
        return NULL;
    }
    Node* enode = l->start;
    while (enode != NULL) {
        if (strcmp(word, enode->data.word) == 0) {
            return &enode->data;
        }
        enode = enode->next;
    }
    return NULL;
}
/*given a word, he looks for the word and deletes his node from the list done. Furthermore, it keeps the linkedlist well linked with the other nodes*/
int delete_from_list(LinkedList* l, char* word) {
    Node* enode = l->start;
    while (enode != NULL) {
        if (strcmp(word, enode->data.word) == 0) {
            if (l->size == 1 || l->size == 0) {
                l->last = NULL;
                l->start = NULL;
            }
            else if (enode->next == NULL) {
                l->last = enode->prev;
                enode->prev->next = NULL;
            }
            else if (enode->prev == NULL) {
                l->start = enode->next;
                enode->next->prev = NULL;
            }
            else{
                enode->next->prev = enode->prev;
                enode->prev->next = enode->next;
            }
            l->size--;
            return SUCCESS;
        }
        enode = enode->next;
    }
    return ERROR;
}
/*it only print on screen the list done by the main*/
void print_list(LinkedList* l) {
    Node* enode = l->start;
    while (enode != NULL) {
        print_word_info(enode->data);
        enode = enode->next;
    }
}

/**
 * Reserve space for the Node element and encapsulate the WordInfo with pointers 
 * to the previous and next element associate with itself in the linked list
 * if node isn't NULL, return the node with the data. 
 */
Node* encapsulateWordInfo(LinkedList* l, WordInfo wi) {
    Node *node = (Node*) malloc(sizeof (Node));
    if (node == NULL) {
        printf("ERROR");
        return NULL;
    } else {
        if (l->size == 0) {
            node->prev = NULL;
            node->next = NULL;
            node->data = wi;
        } else {
            node->prev = l->last;
            node->next = NULL;
            node->data = wi;
        }
        return node;
    }
}
/*this function is called by some other functions and it looks for a word given into a list, if the word exists, it returns True, if not, NULL*/
int buscar_lista(LinkedList* l, char* word) {
    if (l->size == 0) {
        return FALSE;
    }

    Node* enode = l->start;
    while (enode != NULL) {
        if (strcmp(word, enode->data.word) == 0) {
            return TRUE;
        }
        enode = enode->next;

    }
    return FALSE;
}