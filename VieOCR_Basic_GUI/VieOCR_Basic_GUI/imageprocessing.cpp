#include "imageprocessing.h"

using namespace cv;

ImageProcessing::ImageProcessing()
{

}

ImageProcessing::~ImageProcessing()
{

}

bool ImageProcessing::loadImage(const string imagePath)
{
    return(loadImage(mImageGray,imagePath));
}

bool ImageProcessing::loadImage(Mat &image, const string imagePath)
{
    bool ret;
    image = imread(imagePath, CV_LOAD_IMAGE_COLOR);
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

//void ImageProcessing::showImage(Mat image, const string winname)
//{
//    namedWindow(winname, WINDOW_AUTOSIZE);
//    imshow(winname, image);
//    //waitKey();
//}
