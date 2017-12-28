#include "OCR.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <stdio.h>
#include <hunspell/hunspell.hxx>
#include "TCP/TcpUtils/TcpUtils.h"
#include <QDebug>

#define HUNSPELL_DIR "/hunspell"
#define TESSDATA_DIR "/tesseract"

OCR::OCR()
{
    resetPath();
    this->OCR_SYS_ROOT = std::string(getenv("TOOL_SYS_ROOT"));
    std::string envPath = OCR_SYS_ROOT + TESSDATA_DIR;
    setenv("TESSDATA_PREFIX", envPath.c_str(), 1);
}


OCR::~OCR()
{

}

std::string OCR::createTxt(std::string inputPath)
{
    std::string ret = "";
    if(this->loadImage(mImgInput, mInputPath, inputPath))   // TODO: loadImage, preprocessing
    {
        this->genTxtPath(mInputPath, mTxtOutput);
        this->run();
        ret = this->getOutput();
        this->resetPath();
    }
    return ret;
}

bool OCR::loadImage(cv::Mat &image, std::string &storeStr,  const std::string imagePath)
{
    bool ret;
    cv::Mat tmp = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
    if(tmp.data == NULL)
    {
        ret = false;
    }
    else
    {
        image = tmp.clone();
        storeStr = imagePath;
        ret = true;
    }
    return ret;
}

//void cvtGray2Bin(cv::Mat& outImage, cv::Mat inImage)
//{

//}

//void skewCorrector(cv::Mat& outImage, cv::Mat inImage)
//{

//}

//void extWords(std::vector<cv::Mat>& wordArray, cv::Mat image)
//{

//}

//void extChars(std::vector<cv::Mat>& charArray, cv::Mat word)
//{

//}

std::string OCR::getOutput()
{
    return mTxtOutput;
}

// write a string to txt in append mode
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
            des += line;
            des += "\n";
        }
        input.close();
        return true;
    }
    return false;
}

// Input: Path to input file (*.jpg)
// Output: Path to output file (*.txt)
// Generate output filname with the same name
// IMG_0001.jpg => IMG_0001.txt

void OCR::genTxtPath(std::string &txtOutStr, std::string filepath)
{
    std::string outDir = OCR_SYS_ROOT + TMP_PATH;
    std::string filename = basename(filepath.c_str());
    if(!TcpUtils::checkDirExist(outDir.c_str()))
    {
        TcpUtils::createDirectory(outDir.c_str());
    }
    txtOutStr = outDir + TcpUtils::removeExt(filename) + ".txt";
    remove(txtOutStr.c_str());
}

void OCR::resetPath()
{
    mInputPath = "";
    mTxtOutput = "";
    mImgInput.release();
}

std::string OCR::correct(std::string word)
{
    std::string hunPath1 = OCR_SYS_ROOT + HUNSPELL_DIR + "/vi_VN.aff";
    std::string hunPath2 = OCR_SYS_ROOT + HUNSPELL_DIR + "/vi_VN.dic";
    Hunspell hun(hunPath1.c_str(), hunPath2.c_str());
    std::vector<std::string> suggestion;
    if(hun.spell(word, NULL, NULL) == 0)
    {
        qDebug() << "Spelling Error: " << word.c_str();
        suggestion = hun.suggest(word.c_str());
        if(suggestion.size() == 0)
        {
            qDebug() << "Can't find any suggestion for this word " << word.c_str();
            // return word
        }
        else
        {
            qDebug() << "Autocorrect: " << word.c_str() << " to " << suggestion[0].c_str();
            return suggestion[0];
        }
    }
    else
    {
        qDebug() << "Correct spelling" << word.c_str();
        // return word
    }
    return word;
}
