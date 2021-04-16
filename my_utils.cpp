//
// Created by Tal on 31-Oct-20.
//

#include "my_utils.h"

void *renew(void *ptr, int _sizeof_element, int new_size) {
    int i;
    int _sizeof_ptr = sizeof(ptr);
    void *res = (void *) new char[new_size];

    for (i = 0; i < min(_sizeof_ptr, new_size); i++) {
        *((char *) res + i * _sizeof_element) = *((char *) ptr + i * _sizeof_element);
    }
    delete &ptr; /*delete (char *) ptr;*/
    return res;
}

void *cnew(void *ptr, int _sizeof_element, int new_size) {
    int i;
    void *res = (void *) new char[new_size];

    for (i = 0; i < new_size; i++)
        *((char *) res + i * _sizeof_element) = 0;

    delete &ptr; /*delete (char *) ptr;*/
    return res;
}

void *crenew(void *ptr, int _sizeof_element, int new_size) {
    int i;
    int _sizeof_ptr = sizeof(ptr);
    void *res = (void *) new char[new_size];

    for (i = 0; i < min(_sizeof_ptr, new_size); i++)
        *((char *) res + i * _sizeof_element) = *((char *) ptr + i * _sizeof_element);
    for (; i < new_size; i++)
        *((char *) res + i * _sizeof_element) = 0;

    delete &ptr; /*delete (char *) ptr;*/
    return res;
}