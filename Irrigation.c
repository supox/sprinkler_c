#include "Irrigation.h"
#include <stdlib.h>

Irrigation *irrigation_create() {
    Irrigation *i = (Irrigation*)malloc(sizeof(Irrigation));
    if(i != NULL) {
        irrigation_init(i);
    }
    return i;
}

bool irrigation_init(Irrigation *i) {
    i->amount = 0;
    i->mode = TIME;
    i->start_time = 0;
    i->valf_id = 0;
    return true;
}

void irrigation_delete(Irrigation *i) {
    if(i!=NULL)
        irrigation_free_items(i);
    free(i);
}
void irrigation_free_items(Irrigation *i) {
    
}

ListElement* irrigation_create_list() {
    ListElement* root = list_create();
    list_set_delete_function(root, (delete_function)irrigation_delete);
    return root; 
}
