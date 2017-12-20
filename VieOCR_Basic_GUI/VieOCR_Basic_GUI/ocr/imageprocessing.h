#ifndef IMAGEPROCESSING_H
#define IMAGEPROCESSING_H

#include <opencv2/opencv.hpp>
#include "common.h"

class ImageProcessing
{
public:
    ImageProcessing();
    ~ImageProcessing();
    cv::Mat mImageGray;

    bool loadImage(const string imagePath);
    bool loadImage(cv::Mat &image, const string imagePath);
    void cvtGray2Bin(cv::Mat& outImage, cv::Mat inImage);
    void skewCorrector(cv::Mat& outImage, cv::Mat inImage);
    void extWords(vector<cv::Mat>& wordArray, cv::Mat image);
    void extChars(vector<cv::Mat>& charArray, cv::Mat word);


};

#endif // IMAGEPROCESSING_H
