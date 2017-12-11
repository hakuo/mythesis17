/*
 * OCRTool.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#include "OCRTool.h"

using namespace cv;

OCRTool::OCRTool() {

}

OCRTool::~OCRTool() {
    stop();
}

bool OCRTool::readyToRun() {
    return true;
}

void OCRTool::threadLoop() {
    message_t msg;
    while(1) {
        if(popRxQueue(msg) && loadImage(mImage, msg.data)) {
            // TODO cvtToBin
            // TODO extractWord
            // TODO extractChar
            // TODO recognition
            // TODO post processing
            // TODO write to txt file
            // TODO send Msg to OCRMgr
            pushTxQueue(msg);
        }
    }
}


bool OCRTool::loadImage(Mat& image, const char* filepath) {
    bool ret;
    image = imread(filepath, CV_LOAD_IMAGE_GRAYSCALE);
    if(image.data != NULL) {
        ret = true;
    }
    else {
        perror("OCRTool cannot read image");
        ret = false;
    }
    return ret;
}

void OCRTool::showImage(Mat image, const char* title) {
    namedWindow(title, WINDOW_AUTOSIZE);
    imshow(title, image);
    waitKey();
}

bool OCRTool::cvtToBin(Mat& image, uint8_t mode) {
    bool ret;
    switch (mode) {
    case OCRTool::NORMAL_THRESHOLD:
        ret = true;
        // TODO Normal threshold
        break;
    case OCRTool::ADAPTIVE_THRESHOLD_MEAN:
        ret = true;
        adaptiveThreshold(image,            /* Input image */
                image,                      /* Output image */
                255,                        /* maxValue */
                ADAPTIVE_THRESH_MEAN_C,     /* adaptiveMethod */
                CV_THRESH_BINARY,           /* thresholdType */
                45,                         /* blockSize */
                1                           /* C */
        );
        break;
    case OCRTool::ADAPTIVE_THRESHOLD_GAUSSIAN:
        adaptiveThreshold(image,            /* Input image */
                image,                      /* Output image */
                255,                        /* maxValue */
                ADAPTIVE_THRESH_GAUSSIAN_C, /* adaptiveMethod */
                CV_THRESH_BINARY,           /* thresholdType */
                45,                         /* blockSize */
                1                           /* C */
        );
        ret = true;
        break;
    default:
        ret = false;
        break;
    }
    return ret;
}

bool OCRTool::extWord(Mat image, vector<vector<Mat> >words) {
    bool ret;
    return ret;
}

bool OCRTool::extChar(Mat word, vector<vector<Mat> > chars) {
    bool ret;
    return ret;
}












