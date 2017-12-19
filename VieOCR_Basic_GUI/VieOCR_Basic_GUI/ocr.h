#ifndef OCR_H
#define OCR_H

#include "common.h"

class OCR
{
public:
    OCR();
    ~OCR();
    typedef enum: uint8_t {
        BK_OCR=0,
        TESSERACT_OCR=1,
        OCR_TYPE_MAX,
    } ocr_type_t;
};

// create function pointer
typedef OCR* (*CreateOCRToolFP)(void);
#endif // OCR_H