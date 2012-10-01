#include "linked_list.h"
#include <stdlib.h>

bool list_contains(ListElement* root, void* node) {
    for ( ; root->next != NULL ; root = root->next ) {
        if (root->next->node == node) {
            return true;
        }
    }
    return false;
}

bool list_add(ListElement* root, void* node) {
    for ( ; root != NULL ; root = root->next ) {
        if (root->next == NULL) {
            root->next = (ListElement*) malloc(sizeof (ListElement));
            root->next->node = node;
            root->next->next = NULL;
            return true;
        }
    }
    return false;
}

bool list_remove(ListElement* root, void *node) {
    delete_function f = (delete_function)root->node;
    for ( ; root->next != NULL ; root = root->next ) {
        if (root->next->node == node) {
            ListElement* node_to_delete = root->next;
            root->next = root->next->next;
            
            f(node_to_delete->node);
            free(node_to_delete);
            
            return true;
        }
    }
    return false;
}

void list_set_delete_function(ListElement* root, delete_function f) {
    root->node = f;
}

bool list_clear(ListElement* root) {
    delete_function f = (delete_function)root->node;
    ListElement *current_elm, *next_elm;
    
    current_elm = root->next;
    root->next = NULL;
    
    while(current_elm != NULL) {
       next_elm = current_elm->next;
       f(current_elm->node);
       free(current_elm);
       current_elm = next_elm;
    }
    return true;    
}

bool list_empty(ListElement* root) {
    return root->next == NULL;
}

size_t list_count(ListElement* root) {
    size_t count = 0;
    for ( ; root->next != NULL ; root = root->next ) {
        count++;
    }
    return count;
}

ListElement* list_create() {
    ListElement *root = (ListElement*)malloc(sizeof(ListElement));
    if(root) {
        root->node = NULL;
        root->next = NULL;
    }
    list_set_delete_function(root, free);
    return root;
}

bool list_delete(ListElement* root) {
    list_clear(root);
    free(root);
    return true;
}