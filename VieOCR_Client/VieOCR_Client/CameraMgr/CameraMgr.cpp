#include "CameraMgr.h"
#include "TCP/TcpUtils/TcpUtils.h"

CameraMgr::CameraMgr()
{
    stillCam = false;
    isCapture = false;
    TOOL_SYS_ROOT = std::string(getenv("TOOL_SYS_ROOT"));
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
    mCam.set(CV_CAP_PROP_FRAME_WIDTH, 1600);
    mCam.set(CV_CAP_PROP_FRAME_HEIGHT, 1200);
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
    cv::Mat rotFrame;
    std::string tmp_dir = TOOL_SYS_ROOT + TMP_PATH;
    TcpUtils::file_t file;
    file.header.type = TcpUtils::JPG_FILE;
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
            //generate outputpath
            TcpUtils::genFilePath(file, tmp_dir.c_str());
            mOutputPath = file.filepath;
            cv::rotate(frame, rotFrame, cv::ROTATE_90_COUNTERCLOCKWISE);
            cv::imwrite(mOutputPath, rotFrame);
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
    while(this->isCapture == true);
    return mOutputPath;
}
