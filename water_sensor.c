#include "water_sensor.h"

bool sensor_water_reader(Sensor *this) {
    double dCurrentReading = (double)(rand() % 10 + 1); // TODO - load from ports
    this->last_reading_value += dCurrentReading;
    
    return true;
}
