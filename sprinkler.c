#include "sprinkler.h"
#include "logger.h"
#include "string_buffer.h"
#include "url_loader.h"
#include <curl/curl.h>

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

bool sprinkler_read_sensors(Sprinkler* s) {
    bool ret = true;
    int iSensorIndex;
    for (iSensorIndex = 0; iSensorIndex < s->number_of_sensors; iSensorIndex++) {
        double value;
        ret &= sensor_get_reading(&s->sensors[iSensorIndex], &value);
    }
    return ret;
}

Sprinkler* sprinkler_create() {
    Sprinkler* sprinkler = malloc(sizeof (Sprinkler));
    sprinkler_initialize(sprinkler);

    return sprinkler;
}

void sprinkler_delete(Sprinkler* s) {
    free(s);
}

void sprinkler_initialize(Sprinkler* s) {
    int iSensorIndex;
    s->number_of_sensors = 0;
    s->message_queues = CreateQueue(QUEUE_MAX_NUMBER_OF_ELEMENTS);
    for (iSensorIndex = 0; iSensorIndex < MAX_NUMBER_OF_SENSORS; iSensorIndex++) {
        sensor_init(&s->sensors[iSensorIndex]);
    }

    sprinkler_load_config(s);
}

bool sprinkler_load_config(Sprinkler* s) {
    bool ret = false;
    StringBuffer sb;
    ret = get_web_page(SERVER_URL, &sb);
    if(ret) {
        // TODO - Parse response
    }
    return ret;
}
