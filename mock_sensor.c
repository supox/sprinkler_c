#include "mock_sensor.h"
#include <stdlib.h>

bool sensor_mock_reader(Sensor *this, double* value) {
    // generate a number between 1 to 10
    *value = (double)(rand() % 10 + 1);
    return true;
}
