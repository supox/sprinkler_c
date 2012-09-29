/* 
 * File:   key_value_pair.h
 * Author: supox
 *
 * Created on September 29, 2012, 5:52 PM
 */

#ifndef KEY_VALUE_PAIR_H
#define	KEY_VALUE_PAIR_H

typedef struct {
    char *key;
    char* value;
} KeyValuePair;

KeyValuePair* key_value_create_empty();
KeyValuePair* key_value_create(char* key, char*value);
void key_value_delete(KeyValuePair* k);

#endif	/* KEY_VALUE_PAIR_H */

