#ifndef DnnOCR_H
#define DnnOCR_H

#include "OCR.h"

class DnnOCR: public OCR
{
public:
    DnnOCR();
    virtual ~DnnOCR();
    static OCR* Create()
    {
        return new DnnOCR();
    }
    virtual void run();
};

#endif // DnnOCR_H
