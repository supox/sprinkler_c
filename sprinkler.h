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

struct SprinklerStruct;
typedef struct SprinklerStruct Sprinkler;

bool sprinkler_read_sensors(Sprinkler* s);
bool sprinkler_get_messages(Sprinkler* s, char*** messages, int* number_of_messages);
bool sprinkler_clear_messages();

Sprinkler* sprinkler_create();
void sprinkler_delete();

#endif	/* SPRINKLER_H */

