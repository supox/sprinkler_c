/*
 * File:   test_valf.c
 * Author: supox
 *
 * Created on Oct 13, 2012, 9:41:39 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#include "valf.h"
#include "Irrigation.h"
#include "time_functions.h"

void testValf_do_instructions() {
    ListElement* valves_list = valf_create_list();
    ListElement* irrigations_list = irrigation_create_list();
    ListElement* current_valf_node;
    
    time_t current_time = get_time();
    size_t index;
    
    // Initialize valves
    {
        const int valf_ids[] = {4, 6, 5};
        const int valf_ports[] = {1, 2, 4};
        for (index = 0; index < 3; index++) {
            Valf* v = valf_create(valf_ids[index], valf_ports[index]);
            list_add(valves_list, v);
        }
    }

    // Initialize irrigations
    {
        const long times[] = {1, 2, 3, 4};
        const int ids[] = {4, 6, 4, 6};
        const enum IrrigationModes modes[] = {TIME, TIME, TIME, TIME};
        const int amounts[] = {2, 4, 2, 4};
        
        for (index = 0; index < 4; index++) {
            Irrigation* i = irrigation_create();
            i->amount = amounts[index];
            i->mode = modes[index];
            i->start_time = current_time + times[index];
            i->valf_id = ids[index];

            list_add(irrigations_list, i);
        }
    }

    assert(valf_do_instructions(valves_list, irrigations_list));
    
    // Case 1 - Make sure all of the valves are closed
    for(current_valf_node = valves_list->next ; current_valf_node != NULL ; current_valf_node = current_valf_node->next) {
        bool is_open;
        Valf* v = (Valf*) current_valf_node->node;
        assert(valf_get_state(v, &is_open));
        assert(is_open == false);
    }

    // Case 2 - The first should be open.
    ((Irrigation*)(irrigations_list->next->node))->start_time = current_time - 1;
    assert(valf_do_instructions(valves_list, irrigations_list));
    for(current_valf_node = valves_list->next ; current_valf_node != NULL ; current_valf_node = current_valf_node->next) {
        bool is_open;
        bool should_be_open = current_valf_node == valves_list->next;
        Valf* v = (Valf*) current_valf_node->node;
        assert(valf_get_state(v, &is_open));
        assert(is_open == should_be_open );
    }

    // Case 3 - first stays open, the second should be close
    ((Irrigation*)(irrigations_list->next->next->node))->start_time = current_time - 10;
    ((Irrigation*)(irrigations_list->next->next->node))->amount = 5;
    assert(valf_do_instructions(valves_list, irrigations_list));
    for(current_valf_node = valves_list->next ; current_valf_node != NULL ; current_valf_node = current_valf_node->next) {
        bool is_open;
        bool should_be_open = current_valf_node == valves_list->next;
        Valf* v = (Valf*) current_valf_node->node;
        assert(valf_get_state(v, &is_open));
        assert(should_be_open == is_open);
    }
    
    // Case 4 - first closed, second opens
    ((Irrigation*)(irrigations_list->next->node))->start_time = current_time - 4;
    ((Irrigation*)(irrigations_list->next->node))->amount = 2;
    ((Irrigation*)(irrigations_list->next->next->next->next->node))->start_time = current_time - 2;
    ((Irrigation*)(irrigations_list->next->next->next->next->node))->amount = 4;
    assert(valf_do_instructions(valves_list, irrigations_list));
    for(current_valf_node = valves_list->next ; current_valf_node != NULL ; current_valf_node = current_valf_node->next) {
        bool is_open;
        Valf* v = (Valf*) current_valf_node->node;
        const bool should_be_open = v->id == 6;
        assert(valf_get_state(v, &is_open));
        assert(should_be_open == is_open);
    }
}

int main(int argc, char** argv) {
    printf("%%SUITE_STARTING%% test_valf\n");
    printf("%%SUITE_STARTED%%\n");

    printf("%%TEST_STARTED%%  testValf_do_instructions (test_valf)\n");
    testValf_do_instructions();
    printf("%%TEST_FINISHED%% time=0 testValf_do_instructions (test_valf)\n");

    printf("%%SUITE_FINISHED%% time=0\n");

    return (EXIT_SUCCESS);
}
