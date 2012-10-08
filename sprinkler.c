#include "sprinkler.h"
#include "logger.h"
#include "string_buffer.h"
#include "url_loader.h"
#include "time_functions.h"
#include "reading_data.h"
#include "valf.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

static bool sprinkler_load_config(Sprinkler* s);
static bool report_reading_data(const char* url, const reading_data* data);

bool sprinkler_read_sensors(Sprinkler* s) {
    bool ret = true;
    ListElement* root = s->sensors;
    for (root = root->next; root != NULL; root = root->next) {
        Sensor* sensor = (Sensor*) root->node;
        bool will_alarm = false;
        double value = 0;
        ret &= sensor_get_reading(sensor, &value, &will_alarm);
        s->has_alarmed |= will_alarm;
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

void sprinkler_free_elements(Sprinkler* s) {
    list_delete(s->sensors);
    list_delete(s->valves);
}

void sprinkler_delete(Sprinkler* s) {
    sprinkler_free_elements(s);
    free(s);
}

bool sprinkler_initialize(Sprinkler* s) {
    s->id = 0;
    s->refresh_rate = DEFAULT_REFRESH_RATE_SECONDS;
    s->main_valf_delay = 0;
    s->main_valf = -1;
    s->last_report_time = 0;
    s->has_alarmed = false;
    s->sensors = sensor_create_list();
    s->valves  = valf_create_list();

    return sprinkler_load_config(s);
}

static bool sprinkler_load_config(Sprinkler* s) {
    bool ret = false;
    StringBuffer *sb1, *sb2, *sb3;
    sb1 = string_buffer_create();
    sb2 = string_buffer_create();
    sb3 = string_buffer_create();

    ret = get_web_page(SENSORS_CONFIGURATION_URL, sb1);
    if (ret) {
        ret = json_parse_sensors(sb1->memory, s->sensors);
    }
    if (ret) {
        ret = get_web_page(SPRINKLER_CONFIGURATION_URL, sb2);
    }
    if (ret) {
        ret = json_parse_sprinkler_configuration(sb2->memory, s);
    }
    if (ret) {
        ret = get_web_page(SPRINKLER_VALVES_URL, sb3);
    }
    if (ret) {
        ret = json_parse_valves(sb3->memory, s->valves);
    }
    string_buffer_delete(sb1);
    string_buffer_delete(sb2);
    string_buffer_delete(sb3);
    return ret;
}

bool sprinkler_needs_to_report_reading(Sprinkler *s) {
    time_t current_time;
    if (s->has_alarmed)
        return true;

    current_time = get_time();
    return (current_time >= s->last_report_time + s->refresh_rate);
}

bool sprinkler_report_reading(Sprinkler *s) {
    int str_length = 0;
    bool rv = true;
    size_t sensor_index;

    add_to_log("sprinkler_report_reading : Reporting readings.", DUMP);

    ListElement* root_sensors = s->sensors;
    for (root_sensors = root_sensors->next; root_sensors != NULL; root_sensors = root_sensors->next) {
        Sensor* sensor = (Sensor*)root_sensors->node;
        char *url = NULL, *buf = NULL;

        
        if (list_empty(sensor->readings_to_report))
            continue;

        // Build URL
        str_length = asprintf(&url, SENSOR_URL_FORMAT, sensor->id);
        if (str_length > 0) {

            // Report all readings
            ListElement *reports_root = sensor->readings_to_report;
            for (reports_root = reports_root->next; reports_root != NULL; reports_root = reports_root->next) {
                if (!report_reading_data(url, (reading_data*) reports_root->node))
                    rv = false;
            }
            list_clear(sensor->readings_to_report);

            free(url);
        }

        if (str_length < 0) // NO MEMORY.
            return false;
    }

    if (rv) {
        s->last_report_time = get_time();
        s->has_alarmed = false; // reported about the alarm, turn to false.
    }

    return rv;
}

bool report_reading_data(const char* url, const reading_data* data) {
    char *buf;
    int str_length;
    bool post_result;
    StringBuffer request;
    StringBuffer *response;
    bool rv;

    str_length = asprintf(&buf, SENSOR_READING_JSON_FORMAT, data->reading_value, data->reading_time);
    if (str_length < 0)
        return false;

    response = string_buffer_create();

    request.memory = buf;
    request.size = (size_t) str_length;
    request.pos = 0;
    rv = post_web_page(url, &request, response);
    rv &= (strcmp(response->memory, ACK_STRING) == 0);

    string_buffer_delete(response);
    free(buf);
    return rv;
}