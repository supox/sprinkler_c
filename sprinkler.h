/* 
 * File:   sprinkler.h
 * Author: supox
 *
 * Created on September 25, 2012, 12:42 AM
 */

#ifndef SPRINKLER_H
#define	SPRINKLER_H

#include "config.h"
#include "stdbool.h"
#include "sensor.h"
#include "queue.h"

#include <time.h>

typedef struct {
    int id;
    size_t refresh_rate;
    int main_valf_delay;
    int main_valf;
    time_t last_report_time;
    time_t last_irrigation_load_time;
    ListElement* sensors;
    ListElement* valves;
    ListElement* irrigations;
    bool has_alarmed;
    // Queue message_queues;
} Sprinkler;

time_t sprinkler_get_next_task_time(Sprinkler *s);
bool sprinkler_needs_to_do_tasks(Sprinkler* s);
bool sprinkler_do_tasks(Sprinkler* s);

bool sprinkler_initialize(Sprinkler* s);
Sprinkler* sprinkler_create();
void sprinkler_free_elements(Sprinkler*);
void sprinkler_delete(Sprinkler* s);

#endif	/* SPRINKLER_H */

