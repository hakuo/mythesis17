#ifndef OCR_H
#define OCR_H

#include <opencv2/opencv.hpp>
#include "common.h"

using namespace cv;

class OCR
{
public:
    OCR();
    ~OCR();
    Mat mImageRGB;
    Mat mImageBin;
    bool loadImage(const string imagePath);
    bool loadImage(Mat &image, const string imagePath);
    void showImageRGB(const string winname);
    void showImageBin(const string winname);
    void showImage(Mat image, const string winname);
    void cvtRGB2Bin();
    void cvtRGB2Bin(Mat input, Mat &output);
};

#endif // OCR_H
