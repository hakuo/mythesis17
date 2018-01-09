#include <iostream>
#include <opencv2/opencv.hpp>

int main()
{
    cv::VideoCapture cap(1);
    if (!cap.isOpened())
    {
        std::cout << "!!! Failed to open cam"  << std::endl;
        return -1;
    }

    cv::Mat frame;
    for(;;)
    {

        if (!cap.read(frame))
            break;

        cv::imshow("window", frame);

        char key = cvWaitKey(10);
        if (key == 27) // ESC
            break;
    }

    return 0;
}
