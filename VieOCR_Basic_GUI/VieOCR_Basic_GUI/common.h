#ifndef COMMON_H
#define COMMON_H
#include <iostream>
#include <string>
#include <errno.h>
#include <stdint.h>

using namespace std;

typedef union {
    struct
    {
        uint8_t Zoning: 1;
        uint8_t Distance: 1;
        uint8_t Crossing: 1;
    };
    uint8_t value;
}training_feature_t;

#endif // COMMON_H
