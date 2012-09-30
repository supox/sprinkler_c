#include "sprinkler.h"
#include "logger.h"
#include "string_buffer.h"
#include "url_loader.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

static bool sprinkler_load_config(Sprinkler* s);

bool sprinkler_read_sensors(Sprinkler* s) {
    bool ret = true;
    size_t iSensorIndex;
    for (iSensorIndex = 0; iSensorIndex < s->number_of_sensors; iSensorIndex++) {
        double value = 0;
        ret &= sensor_get_reading(&s->sensors[iSensorIndex], &value);
    }
    return ret;
}

Sprinkler* sprinkler_create() {
    Sprinkler* sprinkler = malloc(sizeof (Sprinkler));
    if (sprinkler) {
        if (!sprinkler_initialize(sprinkler)) {
            add_to_log("Could not init sprinkler", ERROR);
            free(sprinkler);
            return NULL;
        }
    }

    return sprinkler;
}

void sprinkler_delete(Sprinkler* s) {
    free(s);
}

bool sprinkler_initialize(Sprinkler* s) {
    int iSensorIndex;
    s->id = 0;
    s->refresh_rate = DEFAULT_REFRESH_RATE;
    s->main_valf_delay = 0;
    s->main_valf = -1;
    s->number_of_sensors = 0;
    s->last_report_time = 0;
    for (iSensorIndex = 0; iSensorIndex < MAX_NUMBER_OF_SENSORS; iSensorIndex++) {
        sensor_init(&s->sensors[iSensorIndex], MOCK);
    }

    return sprinkler_load_config(s);
}

static bool sprinkler_load_config(Sprinkler* s) {
    bool ret = false;
    StringBuffer *sb1, *sb2;
    sb1 = string_buffer_create();
    sb2 = string_buffer_create();

    ret = get_web_page(SENSORS_CONFIGURATION_URL, sb1);
    if (ret) {
        ret = json_parse_sensors(sb1->memory, s->sensors, &s->number_of_sensors, MAX_NUMBER_OF_SENSORS);
    }
    if (ret) {
        ret = get_web_page(SPRINKLER_CONFIGURATION_URL, sb2);
    }
    if (ret) {
        ret = json_parse_sprinkler_configuration(sb2->memory, s);
    }
    string_buffer_delete(sb1);
    string_buffer_delete(sb2);
    return ret;
}

bool sprinkler_needs_to_report_reading(Sprinkler *s) {
    time_t current_time = time(NULL);
    return (current_time - s->last_report_time >= s->refresh_rate);
}

bool sprinkler_report_reading(Sprinkler *s) {
    int str_length = 0;
    bool rv = true;
    size_t sensor_index;
    
    add_to_log("sprinkler_report_reading : Reporting readings.", DUMP);
    
    for (sensor_index = 0; sensor_index < s->number_of_sensors; sensor_index++) {
        char *url=NULL, *buf=NULL;

        str_length = asprintf(&url, SENSOR_URL_FORMAT, s->sensors[sensor_index].id);
        if (str_length > 0) {
            str_length = asprintf(&buf, SENSOR_READING_JSON_FORMAT, s->sensors[sensor_index].last_reading_value, s->sensors[sensor_index].last_reading_time);
            if (str_length > 0) {
                bool post_result;
                StringBuffer *response = string_buffer_create();
                StringBuffer request;
                request.memory = buf;
                request.size = (size_t)str_length;
                request.pos=0;
                post_result = post_web_page(url, &request, response);
                
                if(!post_result)
                    rv = false;
                
                if(strcmp(response->memory, ACK_STRING) != 0)
                    rv = false;
                
                string_buffer_delete(response);
                free(buf);
            }

            free(url);
        }

        if (str_length < 0) // NO MEMORY.
            return false;
    }

    if(rv)
        s->last_report_time = time(NULL);
    
    return rv;
}
