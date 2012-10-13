/* 
 * File:   Irrigation.h
 * Author: supox
 *
 * Created on October 13, 2012, 6:48 PM
 */

#ifndef IRRIGATION_H
#define	IRRIGATION_H

#include "linked_list.h"

#include <stdbool.h>


enum IrrigationModes {
    TIME,
    VOLUME
};

typedef struct {
    time_t start_time;
    int valf_id;
    enum IrrigationModes mode;
    size_t amount;
} Irrigation;

Irrigation *irrigation_create();
bool irrigation_init(Irrigation *i);
void irrigation_delete(Irrigation *i);
void irrigation_free_items(Irrigation *i);
ListElement *irrigation_create_list();

#endif	/* IRRIGATION_H */

