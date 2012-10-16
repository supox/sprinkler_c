#include "reading_data.h"
#include <stdlib.h>

ReadingData* reading_data_create(const time_t time, const double value) {
    ReadingData* data = (ReadingData*)malloc(sizeof(ReadingData));
    if(data!=NULL) {
        data->reading_time = time;
        data->reading_value = value;
    }
    return data;
}

void reading_data_destroy(ReadingData* data) {
    free(data);
}