#ifndef TESSERACTOCR_H
#define TESSERACTOCR_H

#include "ocr.h"

class TesseractOCR: public OCR
{
public:
    TesseractOCR();
    ~TesseractOCR();
    static OCR* Create()
    {
        return new TesseractOCR();
    }
};

#endif // TESSERACTOCR_H
