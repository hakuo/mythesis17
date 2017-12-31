#ifndef CAMERAMGR_H
#define CAMERAMGR_H

#include <opencv2/opencv.hpp>


class CameraMgr
{
public:
    CameraMgr();
    ~CameraMgr();
    bool openCam(int camno);
    void closeCam();
    bool isCamOpen();
    void startCam();
    void stopCam();
    std::string capture();
private:
    cv::VideoCapture mCam;
    volatile bool stillCam;
    volatile bool isCapture;
    std::string mOutputPath;

};

#endif // CAMERAMGR_H
