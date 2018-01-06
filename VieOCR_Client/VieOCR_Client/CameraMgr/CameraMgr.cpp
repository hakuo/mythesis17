#include "CameraMgr.h"

CameraMgr::CameraMgr()
{
    stillCam = false;
}

CameraMgr::~CameraMgr()
{
    stopCam();
    if(isCamOpen())
    {
        closeCam();
    }
}

bool CameraMgr::openCam(int camno)
{
    mCam.open(camno);
    return this->isCamOpen();
}

bool CameraMgr::isCamOpen()
{
    return mCam.isOpened();
}

void CameraMgr::closeCam()
{
    return mCam.release();
}

void CameraMgr::startCam()
{
    stillCam = true;
    cv::Mat frame;
    while(stillCam)
    {
        mCam.read(frame);
        if(frame.empty())
        {
            std::cout << "Camera wasnot started or Not connected to Camera" << std::endl;
            break;
        }
        if(isCapture)
        {
            // TODO: generate file name
            cv::imwrite(mOutputPath, frame);
            isCapture = false;
        }
    }
    stillCam = false;
}

void CameraMgr::stopCam()
{
    stillCam = false;
}

std::string CameraMgr::capture()
{
    if(this->stillCam == false) return NULL;
    this->isCapture = true;
    //wait for saving data
    while(this->isCapture);
    return mOutputPath;
}
