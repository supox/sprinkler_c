/* 
 * File:   config.h
 * Author: supox
 *
 * Created on September 24, 2012, 11:33 PM
 */

#ifndef CONFIG_H
#define	CONFIG_H

#define SERVER_URL "http://localhost:3000/"
#define MAX_NUMBER_OF_SENSORS 16
#define QUEUE_MAX_NUMBER_OF_ELEMENTS 256
#define DEFAULT_REFRESH_RATE 3600 // every hour.
#define LOGGER_FILENAME "/home/supox/Desktop/log.txt"
#define LOGGER_DUMP_MODE_DEFAULT 1
#define SPRINKLER_URL SERVER_URL "sprinklers/1/"
#define SPRINKLER_CONFIGURATION_URL SPRINKLER_URL  "configuration/"
#define SENSORS_CONFIGURATION_URL SPRINKLER_URL "sensors/"

#endif	/* CONFIG_H */

