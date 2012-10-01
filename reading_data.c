#include "reading_data.h"
#include <stdlib.h>

reading_data* reading_data_create(const time_t time, const double value) {
    reading_data* data = (reading_data*)malloc(sizeof(reading_data));
    if(data!=NULL) {
        data->reading_time = time;
        data->reading_value = value;
    }
    return data;
}

void reading_data_destroy(reading_data* data) {
    free(data);
}