/* 
 * File:   valf.h
 * Author: supox
 *
 * Created on October 8, 2012, 11:31 PM
 */

#ifndef VALF_H
#define	VALF_H
#include "linked_list.h"

#include <stdbool.h>

typedef struct {
    int id;
    int port_index;
    bool is_open;
} Valf;

bool valf_set_state(Valf* v, const bool is_open);
bool valf_get_state(Valf* v, bool *is_open);

bool valf_do_instructions(ListElement* valves_list, ListElement* irrigations_list);

Valf* valf_create(const int id, const int port_index);
bool valf_init(Valf* v, const int id, const int port_index);
void valf_delete(Valf*);
void valf_free_elements(Valf*);
ListElement* valf_create_list();


#endif	/* VALF_H */

