#include "ocrfactory.h"
#include "bkocr.h"
#include "tesseractocr.h"

OCRFactory::OCRFactory()
{
    registerOCRTool(OCR::BK_OCR, BKOCR::Create);
    registerOCRTool(OCR::TESSERACT_OCR, TesseractOCR::Create);
}

OCRFactory::~OCRFactory()
{
    mOCRMap.clear();
}

void OCRFactory::registerOCRTool(OCR::ocr_type_t ocr_type, CreateOCRToolFP pfnCreate)
{
    mOCRMap.insert(pair<OCR::ocr_type_t, CreateOCRToolFP>(ocr_type, pfnCreate));
}

OCR* OCRFactory::createOCR(OCR::ocr_type_t ocr_type)
{
    map<OCR::ocr_type_t, CreateOCRToolFP>::iterator it = mOCRMap.find(ocr_type);
    if(it != mOCRMap.end())
    {
        return it->second();
    }
    return nullptr;
}
