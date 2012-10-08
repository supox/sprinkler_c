/* 
 * File:   config.h
 * Author: supox
 *
 * Created on September 24, 2012, 11:33 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

// Constants
#define MAX_NUMBER_OF_SENSORS 16
#define MAX_SENSORS_READING_SIZE 512
#define QUEUE_MAX_NUMBER_OF_ELEMENTS 256
#define DEFAULT_REFRESH_RATE_SECONDS 3600 // every hour.
#define DEFAULT_SENSOR_READING_TIME_DELTA_SECONDS 60 // one minute

// Logger
#define LOGGER_FILENAME "/home/supox/Desktop/log.txt"
#define LOGGER_DUMP_MODE_DEFAULT true

// URLS and server
#define SERVER_URL "http://localhost:3000/"
#define SPRINKLER_URL SERVER_URL "sprinklers/1/"
#define SPRINKLER_CONFIGURATION_URL SPRINKLER_URL  "configuration/"
#define SENSORS_CONFIGURATION_URL SPRINKLER_URL "sensors/"
#define SPRINKLER_VALVES_URL SPRINKLER_URL "valves/"
#define SENSOR_URL_FORMAT SPRINKLER_URL "sensors/%d/create_reading/"
#define SENSOR_READING_JSON_FORMAT "{\"sensor_reading\":{\"sensor_value\":%.0lf,\"read_time\":%u}}"
#define ACK_STRING "{\"result\": \"OK\"}"
#endif	/* CONFIG_H */

