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
    for ( ; root->next != NULL ; root = root->next ) {
        if (root->next->node == node) {
            ListElement* node_to_delete = root->next;
            root->next = root->next->next;
            
            free(node_to_delete->node);
            free(node_to_delete);
            
            return true;
        }
    }
    return false;
}

ListElement* list_create() {
    ListElement *root = (ListElement*)malloc(sizeof(ListElement));
    if(root) {
        root->node = NULL;
        root->next = NULL;
    }
    return root;
}

bool list_delete(ListElement* root) {
    ListElement* next_root;
    
    while(root != NULL) {
       next_root = root->next;
       free(root->node);
       free(root);
       root = next_root;
    }
    
    return true;
}
