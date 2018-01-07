#ifndef OCRFACTORY_H
#define OCRFACTORY_H
#include "OCR.h"
#include <map>

class OCRFactory
{
public:
    OCRFactory();
    ~OCRFactory();
    OCR* createOCR(OCR::ocr_type_t ocr_type);
    static OCRFactory* Get()
    {
        static OCRFactory instance;
        return &instance;
    }

private:
    std::map<OCR::ocr_type_t, CreateOCRToolFP> mOCRMap;   // key: (ocr_type) BK_OCR, Tesseract, ...
                                                     // value: constructor of each type
    void registerOCRTool(OCR::ocr_type_t ocr_type, CreateOCRToolFP pfnCreate);
};

#endif // OCRFACTORY_H
