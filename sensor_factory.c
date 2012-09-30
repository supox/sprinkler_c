#include "sensor_factory.h"

#include "mock_sensor.h"
#include "water_sensor.h"
#include "battery_sensor.h"

// Factory to read_sensor
bool sensor_factory_init(Sensor* s) {
    switch(s->type) {
        case MOCK : default:
            s->read_sensor = sensor_mock_reader;
            break;
        case BATTERY:
            s->read_sensor = sensor_battery_reader;
            break;
        case WATER_READER:
            s->read_sensor = sensor_water_reader;
            break;
        
    }
}
