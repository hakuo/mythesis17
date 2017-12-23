#include "OCR.h"
#include <fstream>
#include "TCP/TcpUtils/TcpUtils.h"
#include <stdio.h>

OCR::OCR()
{

}


OCR::~OCR()
{

}

void OCR::setInput(const std::string filepath, cv::Mat image)
{
    mImgInput = image;
    mFileName = basename(filepath.c_str());
}

std::string OCR::getOutput()
{
    return mTxtOutput;
}

//void OCR::run()
//{

//}

bool OCR::writeStrToTxt(const std::string filepath, std::string src)
{
    std::ofstream output;
    output.open(filepath, std::ios::app);
    if(output.is_open())
    {
        output << src;
        output.close();
        return true;
    }
    return false;
}

bool OCR::readTxtToStr(const std::string filepath, std::string &des)
{
    std::string line;
    des.clear();
    std::ifstream input;
    input.open(filepath, std::ios::in);
    if(input.is_open())
    {
        while (std::getline(input, line)) {
            des = line;
            des += "\n";
        }
        input.close();
        return true;
    }
    return false;
}

void OCR::genOutputPath()
{
    mTxtOutput.clear();
    TcpUtils::createDirectory(UPLOAD_FOLDER);
    mTxtOutput = UPLOAD_FOLDER;
    mTxtOutput += mFileName;
    mTxtOutput += ".txt";
    remove(mTxtOutput.c_str());
}
