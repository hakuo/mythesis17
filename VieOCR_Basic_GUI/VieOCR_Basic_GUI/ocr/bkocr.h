#ifndef BKOCR_H
#define BKOCR_H

#include "ocr.h"

class BKOCR: public OCR
{
public:
    BKOCR();
    ~BKOCR();
    static OCR* Create()
    {
        return new BKOCR();
    }
};

#endif // BKOCR_H
