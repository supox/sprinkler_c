#include "sprinkler.h"
#include "logger.h"
#include "string_buffer.h"
#include "url_loader.h"
#include "time_functions.h"
#include "reading_data.h"
#include "valf.h"
#include "json_parser.h"
#include "Irrigation.h"
#include "MacrosHelper.h"

#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

static bool sprinkler_load_config(Sprinkler* s);
static bool sensor_report_reading_data(const char* url, const reading_data* data);
static bool sprinkler_read_sensors(Sprinkler* s);
static bool sprinkler_report_reading(Sprinkler *s);
static bool sprinkler_needs_to_report_reading(Sprinkler *s);
static bool sprinkler_load_irrigations_instructions(Sprinkler *s);
static bool sprinkler_needs_to_load_irrigations(Sprinkler *s);

time_t sprinkler_get_next_task_time(Sprinkler *s) {
    if( s->last_report_time <= 0 || s->last_irrigation_load_time <= 0)
        return get_time();
    
    return max(s->last_report_time, s->last_irrigation_load_time) + s->refresh_rate;
}

bool sprinkler_needs_to_do_tasks(Sprinkler* s) {
    bool ret;
    ret =
        sprinkler_needs_to_report_reading(s) ||
        sprinkler_needs_to_load_irrigations(s);
    
    return ret;
}

bool sprinkler_do_tasks(Sprinkler* s) {
    bool ret = true;
    
    // Read sensor state, report if needed.
    ret &= sprinkler_read_sensors(s);
    if(ret && sprinkler_needs_to_report_reading(s)) {
        ret &= sprinkler_report_reading(s);
    }
    
    // load irrigation instruction if needed.
    if(sprinkler_needs_to_load_irrigations(s)) {
        ret &= sprinkler_load_irrigations_instructions(s);
    }
    
    // Update valves mode:
    if(ret)
        ret &= valf_do_instructions(s->valves, s->irrigations);
    
    return ret;
}

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

bool sprinkler_needs_to_report_reading(Sprinkler *s) {
    time_t current_time;
    if (s->has_alarmed)
        return true;

    current_time = get_time();
    return (current_time >= s->last_report_time + s->refresh_rate);
}

bool sprinkler_needs_to_load_irrigations(Sprinkler *s) {
    time_t current_time = get_time();
    return (current_time >= s->last_irrigation_load_time + DEFAULT_IRRIGATIONS_REFRESH_TIME);
}

bool sprinkler_load_irrigations_instructions(Sprinkler *s) {
    // load irrigation definitions
    bool ret;
    StringBuffer *sb = string_buffer_create();
    
    add_to_log("sprinkler_load_irrigations : Loading irrigations instructions.", DUMP);
    ret = get_web_page(SPRINKLER_IRRIGATION_URL, sb);
    if (ret) {
        ret = json_parse_irrigations(sb->memory, s->irrigations);
        if(ret)
            s->last_irrigation_load_time = get_time();
    }
    string_buffer_delete(sb);
    
    if(!ret) {
        add_to_log("sprinkler_load_irrigations : failed load irrigations instructions.", ERROR);
    }
    return ret;
}

static bool sprinkler_load_sprinkler_config(Sprinkler *s) {
    bool ret;
    StringBuffer *sb = string_buffer_create();
    ret = get_web_page(SPRINKLER_CONFIGURATION_URL, sb);
    if (ret)
        ret = json_parse_sprinkler_configuration(sb->memory, s);
 
    string_buffer_delete(sb);
    return ret;
}

static bool sprinkler_load_sensors_config(Sprinkler *s) {
    bool ret;
    StringBuffer *sb = string_buffer_create();
    // Load sensors
    ret = get_web_page(SENSORS_CONFIGURATION_URL, sb);
    if (ret)
        ret = json_parse_sensors(sb->memory, s->sensors);
    
    string_buffer_delete(sb);
    return ret;
}

static bool sprinkler_load_valves_config(Sprinkler *s) {
    bool ret;
    StringBuffer *sb = string_buffer_create();
    ret = get_web_page(SPRINKLER_VALVES_URL, sb);
    if (ret)
        ret = json_parse_valves(sb->memory, s->valves);
 
    string_buffer_delete(sb);
    return ret;
}

static bool sprinkler_load_config(Sprinkler* s) {
    bool ret = true;
    
    ret &= sprinkler_load_sprinkler_config(s);
    ret &= sprinkler_load_sensors_config(s);
    ret &= sprinkler_load_valves_config(s);
    ret &= sprinkler_load_irrigations_instructions(s);
    
    return ret;
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
                if (!sensor_report_reading_data(url, (reading_data*) reports_root->node))
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

bool sensor_report_reading_data(const char* url, const reading_data* data) {
    char *buf;
    int str_length;
    StringBuffer request;
    StringBuffer *response;
    bool rv;

    str_length = asprintf(&buf, SENSOR_READING_JSON_FORMAT, data->reading_value, data->reading_time);
    if (str_length < 0)
        return false;

    response = string_buffer_create();

    request.memory = buf;
    request.write_pos = (size_t) str_length;
    request.read_pos = 0;
    rv = post_web_page(url, &request, response);
    rv &= (strcmp(response->memory, ACK_STRING) == 0);

    string_buffer_delete(response);
    free(buf);
    return rv;
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
    list_delete(s->irrigations);
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
    s->last_irrigation_load_time = 0;
    s->has_alarmed = false;
    s->sensors = sensor_create_list();
    s->valves  = valf_create_list();
    s->irrigations  = irrigation_create_list();

    return sprinkler_load_config(s);
}

