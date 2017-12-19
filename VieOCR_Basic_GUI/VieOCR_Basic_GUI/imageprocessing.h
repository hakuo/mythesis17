#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <opencv2/opencv.hpp>
#include "common.h"

class ImageProcessing
{
public:
    ImageProcessing();
    ~ImageProcessing();
    bool loadImage(const string imagePath);
    bool loadImage(cv::Mat &image, const string imagePath);
    cv::Mat mImageGray;

};

#endif // IMAGEPROCESSING_H
