/**
 * Header file with dataTypes and functions related with Tree and Nodes.
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#ifndef TREE_H
#define TREE_H

#include "word_info.h"

typedef struct _Node {
    WordInfo data;
    struct _Node* right;
    struct _Node* left;
} Node;

typedef struct {
    Node* root;
    int size;
} Tree;

void init_tree(Tree* t);
void clear_tree(Tree* t);
int size_tree(Tree* t);
void insert_into_tree(Tree* t, WordInfo wi);
WordInfo* find_in_tree(Tree* t, char* word);
void print_tree(Tree* t);

#endif /* TREE_H */

