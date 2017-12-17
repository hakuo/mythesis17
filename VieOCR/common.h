#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <stdint.h>
#include <errno.h>

using namespace std;

#define UT_TEST

#define BUFFER_SIZE 256
typedef struct
{
    uint8_t msg_id;
    uint8_t data[BUFFER_SIZE];
} message_t;

#endif // COMMON_H
