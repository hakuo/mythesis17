#include <iostream>
#include <opencv2/opencv.hpp>
using namespace std;
using namespace cv;

int main()
{
    cout << "Hello World!" << endl;
    Mat img = imread("/home/cuongdh8/workspace/mythesis17/SampleOCR/scenetext01.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    imshow("xxx", img);
    waitKey();
    return 0;
}
