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
#include <pthread.h>
#include <string>
#include <vector>

using namespace std;

#define FAIL -1
#define SUCCESS 0

#define OCR_INTERNAL_SOCK "./tmp/ocr.sock"

enum {
    DLTOOL_SOCK = 0,
    OCRTOOL_SOCK = 1,
    TTSTOOL_SOCK = 2
};

#endif /* COMMON_H_ */
