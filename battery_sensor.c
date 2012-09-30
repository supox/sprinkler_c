#include "battery_sensor.h"

bool sensor_battery_reader(Sensor *this) {
    this->last_reading_value = 0; // TODO
    return false;
}
