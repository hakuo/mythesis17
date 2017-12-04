/*
 * common.h
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#ifndef COMMON_H_
#define COMMON_H_

#include <iostream>
#include <cstdio>
#include <errno.h>
#include <string>
#include <vector>
#include <stdint.h>
#include <string.h>

using namespace std;

#define FAIL -1
#define SUCCESS 0


#define DATA_LENG 512

//enum {
//    DLTOOL_SOCK = 0x00,
//    OCRTOOL_SOCK,
//    TTSTOOL_SOCK
//};

/* Define internal message format */
typedef struct {
    uint16_t id;
    uint8_t type;
    char data[DATA_LENG];
    bool error;           /* FAIL/SUCCESS */
} message_t;

/* Define message types */
enum {
    NONE = 0x00,
    /* External */
    RQ_VIEOCR,
    RS_VIEOCR,
    /* Internal */
    RQ_DLTOOL,              /* Request to DLTool */
    RQ_OCRTOOL,             /* Request to OCRTool */
    RQ_TTSTOOL,             /* Request to TTSTool */
    RS_DLTOOL,              /* Response from DLTool */
    RS_OCRTOOL,             /* Response from OCRTool */
    RS_TTSTOOL              /* Response from TTSTool */
};


#endif /* COMMON_H_ */
