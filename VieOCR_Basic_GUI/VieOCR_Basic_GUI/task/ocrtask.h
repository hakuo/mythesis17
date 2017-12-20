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

#include "taskthread.h"
#include "common.h"
#include <opencv2/opencv.hpp>

using namespace cv;

#ifdef UT_TEST
#define private public
#endif

class OCRTask : public TaskThread
{
public:
    OCRTask();
    ~OCRTask();

private:
    virtual bool readyToRun();
    virtual void TaskHandler();

    // Preprocessing image functions
//    bool readImage(Mat& image, const string path);
//    bool showImage();
//    bool cvtRGB2Bin();
//    bool extWord();
//    bool extChar();

//    // Training OCR functions
//    void train();
//    void predict();

    // Postprocessing functions
    /* T.B.D */

};

#endif // OCRTASK_H
