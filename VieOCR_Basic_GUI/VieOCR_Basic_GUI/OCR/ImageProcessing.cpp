#include "ImageProcessing.h"

using namespace cv;

ImageProcessing::ImageProcessing()
{

}

ImageProcessing::~ImageProcessing()
{

}

bool ImageProcessing::loadImage(const std::string imagePath)
{
    return(loadImage(mImageGray,imagePath));
}

bool ImageProcessing::loadImage(Mat &image, const std::string imagePath)
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


