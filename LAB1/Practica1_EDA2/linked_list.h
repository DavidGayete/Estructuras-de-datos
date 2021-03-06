#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "word_info.h"

typedef struct _Node {
    WordInfo data;
    struct _Node* next;
    struct _Node* prev;
} Node;

typedef struct {
    Node* start;
    Node* last;
    int size;
} LinkedList;

void init_list(LinkedList* l);
void clear_list(LinkedList* l);

int insert_into_list(LinkedList* l, WordInfo wi);
WordInfo* find_first_in_list(LinkedList* l, char* word);
int delete_from_list(LinkedList* l, char* word);

void print_list(LinkedList* l);

Node* encapsulateWordInfo(LinkedList* l, WordInfo wi);
int buscar_lista(LinkedList* l, char* word);
#endif
