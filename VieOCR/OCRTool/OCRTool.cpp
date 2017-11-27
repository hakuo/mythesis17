/*
 * OCRTool.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#include "OCRTool.h"

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

bool OCRTool::loadImage(cv::Mat& image, const char* filepath) {
    bool ret;
    image = cv::imread(filepath, CV_LOAD_IMAGE_GRAYSCALE);
    if(image.data != NULL) {
        ret = true;
    }
    else {
        perror("OCRTool cannot read image");
        ret = false;
    }
    return ret;
}
















