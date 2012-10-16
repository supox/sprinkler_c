#include "valf.h"
#include "linked_list.h"
#include "Irrigation.h"
#include "time_functions.h"
#include "logger.h"
#include <stdlib.h>
#include <stdio.h>

bool valf_set_state(Valf* v, const bool is_open) {
    if(v->is_open != is_open) {
        // Mock placeholder
        v->is_open = is_open;
        
        // log
        {
            char *log_line;
            int size_of_line;
            size_of_line = asprintf(&log_line, "Setting state of valf %d (port %d) to %d", v->id, v->port_index, is_open);
            if(size_of_line>0) {
                add_to_log(log_line, NORMAL);
                free(log_line);
            }
        }
        
    }
    return true;
}

bool valf_get_state(Valf* v, bool *is_open) {
    // Mock placeholder
    *is_open = v->is_open;
    return true;
}

bool valf_do_instructions(ListElement* valves_list, ListElement* irrigations_list) {
    time_t current_time = get_time();
    ListElement *current_valf_node, *current_irrigation_node;
    for (current_valf_node = valves_list->next; current_valf_node != NULL; current_valf_node = current_valf_node->next) {
        Valf* v = (Valf*) current_valf_node->node;
        bool is_open = false;
        // TODO - build a hash instead of iterate over all irrigation every time...
        for (current_irrigation_node = irrigations_list->next; current_irrigation_node != NULL; current_irrigation_node = current_irrigation_node->next) {
            Irrigation* irrigation = (Irrigation*) current_irrigation_node->node;
            if (v->id == irrigation->valf_id) {
                if(irrigation->mode == TIME) {
                        is_open |=
                                current_time >= irrigation->start_time &&
                                current_time <= irrigation->start_time + irrigation->amount;
                } else if(irrigation->mode == VOLUME) {
                    // TODO!!
                    add_to_log("valf_do_instructions - volume irrigation not implemented.", ERROR);
                    return false;
                }
            }
        }
        valf_set_state(v, is_open);
    }
    return true;
}

Valf* valf_create(const int id, const int port_index) {
    Valf* valf = (Valf*) malloc(sizeof (Valf));
    if (valf != NULL)
        valf_init(valf, id, port_index);
    return valf;
}

bool valf_init(Valf* v, const int id, const int port_index) {
    bool ret = true;
    v->id = id;
    v->port_index = port_index;
    
    if(id >= 0 && port_index >= 0) { // Set initial state to close
        v->is_open = true;
        ret = valf_set_state(v, false);
    }
    else
        v->is_open = false;
    
    return ret;
}

void valf_delete(Valf* v) {
    if (v != NULL)
        valf_free_elements(v);
    free(v);
}

void valf_free_elements(Valf* v) {

}

ListElement* valf_create_list() {
    ListElement* root = list_create();
    list_set_delete_function(root, (delete_function) valf_delete);
    return root;
}

