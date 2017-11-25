/*
 * OCRTool.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#include "OCRTool.h"

OCRTool* OCRTool::m_me = NULL;

OCRTool::OCRTool() {
    mOCRToolThread = 0;
}

OCRTool::~OCRTool() {

}

void OCRTool::run(const char* filepath) {
    if(readyToRun(filepath)) {
        if(pthread_create(&mOCRToolThread, NULL, OCRTool::OCRToolThread, this) < 0) {
            perror("OCRTool cannot create thread");
        }
    }
}

void* OCRTool::OCRToolThread(void* arg) {
    m_me = reinterpret_cast<OCRTool*> (arg);
    m_me->startOCRTool();
    return NULL;
}

void OCRTool::startOCRTool() {
    // TODO cvtToBin
    // TODO extractWord
    // TODO extractChar
    // TODO recognition
    // TODO post processing
    // TODO write to txt file
    // TODO send Msg to OCRMgr


}

bool OCRTool::readyToRun(const char* filepath) {
    return (loadImage(mImage, filepath) == SUCCESS);
}

int OCRTool::loadImage(cv::Mat& image, const char* filepath) {
    int ret;
    image = cv::imread(filepath, CV_LOAD_IMAGE_GRAYSCALE);
    if(image.data != NULL) {
        ret = SUCCESS;
    }
    else {
        perror("OCRTool cannot read image");
        ret = FAIL;
    }
    return ret;
}
















