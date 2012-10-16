#include "sensor_factory.h"

#include "mock_sensor.h"
#include "water_sensor.h"
#include "battery_sensor.h"

// Factory to read_sensor
bool sensor_factory_init(Sensor* s) {
    switch(s->type) {
        case MOCK:
            s->read_sensor = sensor_mock_reader;
            return true;
        case BATTERY:
            s->read_sensor = sensor_battery_reader;
            return true;
        case WATER_READER:
            s->read_sensor = sensor_water_reader;
            return true;
        default:
            return false;
    }
}
