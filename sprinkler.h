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
    int refresh_rate;
    int main_valf_delay;
    int main_valf;
    time_t last_report_time;
    ListElement* sensors;
    ListElement* valves;
    bool has_alarmed;
    // Queue message_queues;
    
    // TODO - add valves
} Sprinkler;

bool sprinkler_read_sensors(Sprinkler* s);
bool sprinkler_report_reading(Sprinkler *s);
bool sprinkler_needs_to_report_reading(Sprinkler *s);

bool sprinkler_initialize(Sprinkler* s);
Sprinkler* sprinkler_create();
void sprinkler_free_elements(Sprinkler*);
void sprinkler_delete(Sprinkler* s);

#endif	/* SPRINKLER_H */

