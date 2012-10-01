/* 
 * File:   linked_list.h
 * Author: supox
 *
 * Created on October 1, 2012, 8:59 PM
 */

#ifndef LINKED_LIST_H
#define	LINKED_LIST_H

#include <stdbool.h>
#include <stdlib.h>

struct list_el{
    void* node;
    struct list_el* next;
};

typedef struct list_el ListElement;

typedef void(*delete_function)(void*);


// List functions
bool list_add(ListElement* root, void* node);
bool list_contains(ListElement* root, void* node);
bool list_remove(ListElement* root, void *node);
bool list_empty(ListElement* root);
bool list_clear(ListElement* root);
void list_set_delete_function(ListElement* root, delete_function f);
size_t list_count(ListElement* root);

ListElement* list_create();
bool list_delete(ListElement* root);

#endif	/* LINKED_LIST_H */

