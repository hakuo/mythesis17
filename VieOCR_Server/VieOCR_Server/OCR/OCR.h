#ifndef OCR_H
#define OCR_H

#include "common.h"
#include <opencv2/imgproc.hpp>

class OCR
{
public:
    OCR();
    virtual ~OCR();
    typedef enum: uint8_t {
        TESSERACT_OCR=0,
        DNN_OCR=1,
        OCR_TYPE_MAX,
    } ocr_type_t;
    virtual void run() = 0;
    static bool loadImage(cv::Mat &image, const std::string imagePath);
    void setInputPath(std::string str);
    std::string createTxt(std::string inputPath);
    std::string createTxt(cv::Mat image);
    void deSkew(cv::Mat &cropped, cv::Mat image);
    void lineSegment(std::vector<cv::Mat>& lineArray, cv::Mat image);
protected:
    bool isRun;
    std::string OCR_SYS_ROOT;
    cv::Mat mImgInput;
    std::string mInputPath;
    std::string mTxtOutput;
    void setImgInput(cv::Mat img);
    void cvtGray2Bin(cv::Mat& outImage, cv::Mat inImage);
    bool writeStrToTxt(const std::string filepath, std::string src);
    bool readTxtToStr(const std::string filepath, std::string &des);
    void genTxtPath(std::string &txtOutStr, std::string filepath);
    std::string getOutput();
    void resetPath();
    std::string correct(std::string word);
};

// create function pointer
typedef OCR* (*CreateOCRToolFP)(void);
#endif // OCR_H
