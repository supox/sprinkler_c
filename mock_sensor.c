#include "mock_sensor.h"
#include <stdlib.h>

bool sensor_mock_reader(Sensor *this) {
    // generate a number between 1 to 10
    this->last_reading_value = (double)(rand() % 10 + 1);
    return true;
}
