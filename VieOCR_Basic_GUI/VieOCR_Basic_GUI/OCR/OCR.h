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

    bool writeStrToTxt(const std::string filepath, std::string src);
    bool readTxtToStr(const std::string filepath, std::string &des);
    void setInput(const std::string filepath, cv::Mat image);
    std::string getOutput();

protected:
    cv::Mat mImgInput;
    std::string mFileName;
    std::string mTxtOutput;
    void genOutputPath();
    std::string correct(std::string word);
};

// create function pointer
typedef OCR* (*CreateOCRToolFP)(void);
#endif // OCR_H
