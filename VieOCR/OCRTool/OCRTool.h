/*
 * OCRTool.h
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#ifndef OCRTOOL_H_
#define OCRTOOL_H_

#include <opencv2/opencv.hpp>
#include "../common.h"
#include "../utils/file.h"


class OCRTool {
public:
    OCRTool();
    virtual ~OCRTool();
    void run(const char* filepath);

private:
    static OCRTool* m_me;

    /* Define member variable */
    cv::Mat mImage;
    pthread_t mOCRToolThread;

    /* Thread */
    bool readyToRun(const char* filepath);
    static void* OCRToolThread(void* arg);

    /* OCR utilities */
    void startOCRTool();
    int loadImage(cv::Mat& image, const char* filepath);
    int showImage(cv::Mat image, const char* title);
    int cvtToBin(cv::Mat image, int mode);
    int extWord(cv::Mat image, vector<vector<cv::Mat> >words);
    int extChar(cv::Mat word, vector<vector<cv::Mat> > chars);

    /* Training Algorithms */


    /* Connect to OCRMgr */

};

#endif /* OCRTOOL_H_ */
