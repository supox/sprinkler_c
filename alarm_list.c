#include "alarm_list.h"
#include <stdlib.h>

bool alarm_list_will_alarm(AlarmList *root, const double sensor_value) {
    for(root = root->next; root != NULL ; root = root->next) {
        if (alarm_will_alarm(root->node, sensor_value))
            return true;
    }
    return false;
}

// List functions

bool alarm_list_contains(AlarmList* root, Alarm* node) {
    for ( ; root->next != NULL ; root = root->next ) {
        if (root->next->node == node) {
            return true;
        }
    }
    return false;
    
}

bool alarm_list_add(AlarmList* root, Alarm* node) {
    for ( ; root != NULL ; root = root->next ) {
        if (root->next == NULL) {
            root->next = (AlarmList*) malloc(sizeof (AlarmList));
            root->next->node = node;
            root->next->next = NULL;
            return true;
        }
    }

    return false;

}
bool alarm_list_remove(AlarmList* root, Alarm *node) {
    for ( ; root->next != NULL ; root = root->next ) {
        if (root->next->node == node) {
            AlarmList* node_to_delete = root->next;
            root->next = root->next->next;
            
            alarm_delete(node_to_delete->node);
            free(node_to_delete);
            
            return true;
        }
    }
    return false;
}

AlarmList* alarm_list_create() {
    AlarmList *root = (AlarmList*)malloc(sizeof(AlarmList));
    if(root) {
        root->node = NULL;
        root->next = NULL;
    }
    return root;
}

bool alarm_list_delete(AlarmList* root) {
    AlarmList* next_root;
    
    while(root != NULL) {
       next_root = root->next;
       alarm_delete(root->node);
       free(root);
       root = next_root;
    }
    
    return true;
}
