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
#include "../Thread/Thread.h"
#include "../utils/file.h"


class OCRTool: public Thread {
    enum {
        NORMAL_THRESHOLD,
        ADAPTIVE_THRESHOLD_MEAN,
        ADAPTIVE_THRESHOLD_GAUSSIAN
    };
public:
    OCRTool();
    virtual ~OCRTool();

private:
    /* Define member variable */
    cv::Mat mImage;

    /* Thread */
    virtual bool readyToRun();
    virtual void threadLoop();

    /* OCR utilities */
    bool loadImage(cv::Mat& image, const char* filepath);
    void showImage(cv::Mat image, const char* title);
    bool cvtToBin(cv::Mat& image, uint8_t mode);
    bool extWord(cv::Mat image, vector<vector<cv::Mat> >words);
    bool extChar(cv::Mat word, vector<vector<cv::Mat> > chars);

    /* Training Algorithms */

};

#endif /* OCRTOOL_H_ */
