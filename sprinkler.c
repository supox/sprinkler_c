#include "sprinkler.h"
#include <stdlib.h>

struct SprinklerStruct {
    int number_of_sensors;
    Sensor* sensors[MAX_NUMBER_OF_SENSORS];
    Queue message_queues;
    
    // TODO - add valves
};


bool sprinkler_read_sensors(Sprinkler* s) {
    return false;
}

bool sprinkler_get_messages(Sprinkler* s, char*** messages, int* number_of_messages) {
    return false;
}

bool sprinkler_clear_messages() {
    return false;
}

Sprinkler* sprinkler_create() {
    int iSensorIndex;
    Sprinkler* sprinkler = malloc(sizeof(Sprinkler));
    
    sprinkler->number_of_sensors = 0;
    sprinkler->message_queues = CreateQueue(QUEUE_MAX_NUMBER_OF_ELEMENTS);
    for(iSensorIndex = 0 ; iSensorIndex < MAX_NUMBER_OF_SENSORS ; iSensorIndex) {
        sprinkler->sensors[iSensorIndex] = sensor_create();
    }
    return sprinkler;
    
}
void sprinkler_delete(Sprinkler* sprinkler) {
    int iSensorIndex;
    for(iSensorIndex = 0 ; iSensorIndex < MAX_NUMBER_OF_SENSORS ; iSensorIndex) {
        sensor_delete(sprinkler->sensors[iSensorIndex]);
    }
    free(sprinkler);
}
