#include "OCR_Task.h"

OCRTask::OCRTask()
{

}

OCRTask::~OCRTask()
{

}

/*
 * @function: readyToRun
 * @description: condition to run OCRTask
 * (create a thread handles OCRTask)
 * @author: Duong Hac Cuong
 * @created: December 16, 2017
 */
bool OCRTask::readyToRun()
{
    bool ret = false;
    return ret;
}

/*
 * @function: TaskHandler
 * @description: Main function of OCRTask
 * @author: Duong Hac Cuong
 * @created: December 16, 2017
 */
void OCRTask::TaskHandler()
{
    // Step 1: Check rxQueue to receive image path

    // Step 2: Load image and Preprocessing

    // Step 3: Segmentation

    // Step 4: Training data / Recognition

    // Step 5: Postprocessing

    // Step 6: push output to txQueue
}

/*
 * @function: loadImage
 * @desciption: load Image from file and store in a Matrix
 * @author: Duong Hac Cuong
 * @created: December 16, 2017
 */
//bool OCRTask::loadImage(Mat& image, const string path)
//{
//    bool ret;
//    image = imread(path, CV_LOAD_IMAGE_ANYCOLOR);
//    if(image.data == NULL)
//    {
//        perror("Error in loading image");
//        ret = false;
//    }
//    else
//    {
//        ret = true;
//    }
//    return ret;
//}

//void OCRTask::showImage(Mat image, const string winname)
//{
//    namedWindow(winname, WINDOW_AUTOSIZE);
//    imshow(winname, image);
//    waitKey();
//}

































