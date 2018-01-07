#ifndef TESSERACTOCR_H
#define TESSERACTOCR_H

#include "OCR.h"

class TesseractOCR: public OCR
{
public:
    TesseractOCR();
    virtual ~TesseractOCR();
    static OCR* Create()
    {
        return new TesseractOCR();
    }

    virtual void run();
private:

};

#endif // TESSERACTOCR_H
