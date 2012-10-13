#include "valf.h"
#include "linked_list.h"
#include "Irrigation.h"
#include <stdlib.h>

Valf* valf_create() {
    Valf* valf = (Valf*)malloc(sizeof(valf));
    if(valf!=NULL)
        valf_init(valf, -1, -1);
    return valf;
}

bool valf_init(Valf* v, const int id, const int port_index) {
    v->id = id;
    v->port_index = port_index;
    return true;
}

void valf_delete(Valf* v) {
    if(v!=NULL)
        valf_free_elements(v);
    free(v);
}

void valf_free_elements(Valf* v) {
    
}

ListElement* valf_create_list() {
    ListElement* root = list_create();
    list_set_delete_function(root, (delete_function)valf_delete);
    return root;
}
