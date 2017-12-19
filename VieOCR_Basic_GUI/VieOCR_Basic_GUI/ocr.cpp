#include "ocr.h"

OCR::OCR()
{

}

OCR::~OCR()
{

}

bool OCR::loadImage(const string imagePath)
{
    return loadImage(mImageGray, imagePath);
}
bool OCR::loadImage(Mat &image, const string imagePath)
{
    bool ret;
    image = imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
    if(image.data == NULL)
    {
        perror("Error in loading image");
        ret = false;
    }
    else
    {
        ret = true;
    }
    return ret;
}

void OCR::showImageGray(const string winname)
{
    if(mImageGray.data != NULL)
    {
        showImage(mImageGray, winname);
    }
}

void OCR::showImageBin(const string winname)
{
    if(mImageBin.data != NULL)
    {
        showImage(mImageBin, winname);
    }
}

void OCR::showImage(Mat image, const string winname)
{
    namedWindow(winname, WINDOW_AUTOSIZE);
    imshow(winname, image);
}

void OCR::cvtRGB2Bin()
{
    return cvtRGB2Bin(mImageGray, mImageBin);
}

void OCR::cvtRGB2Bin(Mat input, Mat &output)
{
    // Method 1: Adaptive threshold Mean C
    adaptiveThreshold(input, output, 255, ADAPTIVE_THRESH_MEAN_C, CV_THRESH_BINARY, 45, 1);
    // Method 2: Adaptive threshold Gaussian C
    //adaptiveThreshold(input, output, 255, ADAPTIVE_THRESH_GAUSSIAN_C, CV_THRESH_BINARY, 45, 1);
}
