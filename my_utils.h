//
// Created by Tal on 31-Oct-20.
//

#ifndef MY_T1_MY_UTILS_H
#define MY_T1_MY_UTILS_H

inline int min(int a, int b){
    return a < b ? a : b;
}
inline int max(int a, int b){
    return a > b ? a : b;
}

void *renew(void *ptr, int _sizeof_element, int new_size);
void *cnew(void *ptr, int _sizeof_element, int new_size);
void *crenew(void *ptr, int _sizeof_element, int new_size);
#endif //MY_T1_MY_UTILS_H
