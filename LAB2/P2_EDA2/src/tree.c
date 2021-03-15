/**
 * Functions related with the dataType Tree and Node.
 * 
 * Eduard Masip         NIA: 207322
 * David Gayete         NIA: 204921
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "commons.h"
#include "tree.h"

/**
 * <<Recursive function>> that receive a Node as a parameter, check if the node is NULL and if is not NULL
 * it calls itself with the left node of the actual.
 * When the node passed as parameter is NULL, go back on the position that it has called and it call itself other time but with the right node
 * of the current.
 * Finally frees the current node with which the function has been called and return a previous level recursion.
 * With this pattern we get the PostOrder method to go over the tree.
 */
void clearPostOrder(Node* node)
{ 
    if(node != NULL){
        clearPostOrder(node->left);
        clearPostOrder(node->right);
        free(node);
    }
}

/**
 * This function receive a WordInfo as parameter and reserve memory space for a Node.
 * Initialize the left and right Node pointer to NULL, and copy the info of the WordInfo received in the node created. 
 * Finally return the Node created.
 */
Node *createNode(WordInfo wi)
{
    Node* enode = (Node*) malloc(sizeof(Node));
    enode->left = NULL;
    enode->right = NULL;
    strcpy(enode->data.word, wi.word);
    strcpy(enode->data.definition, wi.definition);
    enode->data.pos = wi.pos;
    return enode;
}

/**
 * <<Recursive function>> This function receive a node and a string (word) as a parameter. 
 * Check if the word is greater (alphabetically) than the node's word. If is greater, checks 
 * if the node->right is NULL, if it NULL means that word does not exist in the dictionary (Tree).
 * Else it calls itself but now with the node->right and the same word.
 * 
 * If is smaller (alphabetically) than the node's word, follow the same process but with the node->left.
 * 
 * Else means that the node's word and the word passed as parameter is the same and return the Node.
 */
Node* findNode(Node* node, char* word)
{
    if(strcmp(word, node->data.word) > 0){
        if(node->right == NULL){
            return NULL;
        }
        else{
            findNode(node->right, word);
        }
    }
    else if(strcmp(word, node->data.word) < 0){
        if(node->left == NULL){
            return NULL;
        }
        else{
            findNode(node->left, word);
        }
    }
    else{
        return node;
    } 
}

/**
 * <<Recursive function>> that receive a Node as a parameter, check if the node is NULL and if is not NULL
 * it calls itself with the left node of the actual.
 * When the node passed as parameter is NULL, go back on the position that it has called and calls the function printWordInfo with the
 * current node. After it call itself other time but with the right node.
 * With this pattern we get the InOrder method to go over the tree.
 */
void printInOrder(Node* node)
{ 
    if(node != NULL){
        printInOrder(node->left);
        print_word_info(node->data);
        printInOrder(node->right);
    }
}

/**
 * This function receive a pointer of tree as parameter, and initialize its values.
 * Put the size to 0 and the root to NULL.
 */
void init_tree(Tree* t){
    t->size = 0;
    t->root = NULL;
}

/**
 * This function is called to clear the tree. First check if the tree size is equals to 0.
 * If so, only prints a message that warns at the user that the tree is empty.
 * Else call the recursive function clearPostOrder with the root Node.
 * Finally puts the tree size to zero.
 */
void clear_tree(Tree* t){
    if(t->size == 0){
        printf("Arbre Buit\n");
    }
    else{
        clearPostOrder(t->root);
    }
    t->size = 0;
}

/**
 * <<Recursive function>> This function receive a WordInfo and a Node as parameter. 
 * Check if the WordInfo word is greater (alphabetically) than the node's word. If is greater, checks 
 * if the node->right is NULL, if it NULL means that this position is the correct position for the Node, and 
 * calls the function createNode with the WordInfo. If the node returned is not NULL, assigns at right of the current node
 * the node returned and puts the inserted variable at TRUE, if is NULL put inserted at FALSE.
 * Else it calls itself but now with the node->right and the same WordInfo.
 * 
 * If is smaller (alphabetically) than the node's word, follow the same process but with the node->left.
 * 
 * Else means that this WordInfo it already exist at the Tree and warn the user and put inserted to FALSE.
 * 
 * Finally the function return the inserted variable.
 */
int buscarPosicio(WordInfo wi, Node* node){
    Node* result;
    int inserted;
    if(strcmp(wi.word, node->data.word) > 0){
        if(node->right == NULL){
            result = createNode(wi);
            if(result != NULL){
                node->right = result;
                inserted = TRUE;
            }
            else{
                inserted = FALSE;
            }
        }
        else{
            inserted = buscarPosicio(wi, node->right);
        }
    }
    else if(strcmp(wi.word, node->data.word) < 0){
        if(node->left == NULL){
            result = createNode(wi);
            if(result != NULL){
                node->left = result;
                inserted = TRUE;
            }
            else{
                inserted = FALSE;
            }
        }
        else{
            inserted = buscarPosicio(wi, node->left);
        }
    }
    else{
        printf("Ja existeix la paraula\n");
        inserted = FALSE;
        
    } 
    return inserted;
}

/**
 * This function receive a pointer to Tree and a WordInfo.
 * If size of the Tree is equal to zero, calls createNode with the WordInfo, and if the value returned
 * is not NULL, assign to the Tree root the value and increments by one the size.
 * Else, call the function buscarPosicio with the WordInfo and the root. If this function return TRUE
 * the size of the tree is incremented by one!
 */
void insert_into_tree(Tree* t, WordInfo wi){
    if(t->size == 0){
        Node* result = createNode(wi);
        if(result != NULL){
            t->root = result;
            t->size++;
        }
    }
    else{
        int value = buscarPosicio(wi, t->root);
        if(value == TRUE){
            t->size++;
        }
    }
}

/**
 * This function is called with pointer of Tree and a string (Word).
 * If the size of the tree is not equal zero, call the function findNode with the root Node of the Tree and
 * the String (Word). The returned value (Node) is saved at variable result.
 * If result is not NULL, returns the result->data. Else return NULL.
 */
WordInfo* find_in_tree(Tree* t, char* word){
    Node* enode = t->root;
    Node* result;
    if(t->size != 0){
        result = findNode(enode, word); 
    }
    if(result != NULL){
        return &result->data;
    }
    return NULL;
}

/**
 * Return the sixe of the Tree.
 */
int size_tree(Tree* t){
    return t->size;
}

/**
 * This function is called to print the tree. First check if the tree size is equals to 0.
 * If so, only prints a message that warns at the user that the tree is empty.
 * Else call the recursive function printInOrder with the root Node.
 */
void print_tree(Tree* t){
    if(t->size == 0){
        printf("Arbre Buit");
    }
    else{
        printInOrder(t->root);
    }
}
