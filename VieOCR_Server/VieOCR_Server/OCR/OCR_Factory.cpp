#include "OCR_Factory.h"
#include "DnnOCR.h"
#include "TesseractOCR.h"

OCRFactory::OCRFactory()
{
    registerOCRTool(OCR::DNN_OCR, DnnOCR::Create);
    registerOCRTool(OCR::TESSERACT_OCR, TesseractOCR::Create);
}

OCRFactory::~OCRFactory()
{
    mOCRMap.clear();
}

void OCRFactory::registerOCRTool(OCR::ocr_type_t ocr_type, CreateOCRToolFP pfnCreate)
{
    mOCRMap.insert(std::pair<OCR::ocr_type_t, CreateOCRToolFP>(ocr_type, pfnCreate));
}

OCR* OCRFactory::createOCR(OCR::ocr_type_t ocr_type)
{
    std::map<OCR::ocr_type_t, CreateOCRToolFP>::iterator it = mOCRMap.find(ocr_type);
    if(it != mOCRMap.end())
    {
        return it->second();
    }
    return nullptr;
}
