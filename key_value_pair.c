#include "key_value_pair.h"
#include <stdlib.h>

KeyValuePair* key_value_create_empty() {
    KeyValuePair* k = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    if(k) {
        k->key=(char*) malloc(sizeof(char)*256);
        k->value=(char*) malloc(sizeof(char)*256);
    }
    return k;
}

KeyValuePair* key_value_create(char* key, char*value) {
    KeyValuePair* k = (KeyValuePair*)malloc(sizeof(KeyValuePair));
    if(k) {
        k->key=strdup(key);
        k->value=strdup(value);
    }
    return k;
}

void key_value_delete(KeyValuePair* k) {
    if(k) {
        free(k->key);
        free(k->value);
    }
    free(k);
}
