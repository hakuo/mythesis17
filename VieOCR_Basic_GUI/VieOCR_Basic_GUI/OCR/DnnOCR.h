#ifndef DnnOCR_H
#define DnnOCR_H

#include "OCR.h"

class DnnOCR: public OCR
{
public:
    DnnOCR();
    ~DnnOCR();
    static OCR* Create()
    {
        return new DnnOCR();
    }
};

#endif // DnnOCR_H
