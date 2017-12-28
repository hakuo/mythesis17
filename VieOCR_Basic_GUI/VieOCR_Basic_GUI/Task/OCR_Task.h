/*
 * * OCRTask (Optimal Character Recognition) recognizes characters
 * from an Image and writes it to a text file.
 * * Dependencies: OpenCV
 * * Input: Path to image which needs to recognize
 * * Output: Path to text file
 * * Author: Duong Hac Cuong (BKU)
 * * Created: December 16, 2017
 */
#ifndef OCRTASK_H
#define OCRTASK_H

#include "TaskThread.h"
#include "common.h"
#include "OCR/OCR.h"
#include "OCR/ImageProcessing.h"

class OCRTask : public TaskThread
{
public:
    OCRTask();
    OCRTask(OCR::ocr_type_t ocr_type);
    virtual ~OCRTask();

private:
    virtual bool readyToRun();
    virtual void TaskHandler();

    OCR* pOCRinstance;
};

#endif // OCRTASK_H
