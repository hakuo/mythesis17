#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stdint.h>

using namespace std;

#define BUFFER_SIZE 256
typedef struct
{
    uint8_t msg_id;
    char data[BUFFER_SIZE];
} message_t;

#endif // COMMON_H
