#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>
#include "TesseractOCR.h"
#include "OCR_Utils/include/text.hpp"
#include <QDebug>

using namespace std;
using namespace cv;
using namespace cv::text;

#define WHITE_LIST "aàáảãạăằắẳẵặâầấẩẫậbcdđeèéẻẽẹêềếểễệfghiìíỉĩịjklmnoòóỏõọôồốổỗộơờớởỡợpqrstuùúủũụưừứửữựvwxyzAÀÁẢÃẠĂẰẮẲẴẶÂẦẤẨẪẬBCDĐEÈÉẺẼẸÊỀẾỂỄỆFGHIÌÍỈĨỊJKLMNOÒÓỎÕỌÔỒỐỔỖỘƠỜỚỞỠỢPQRSTUÙÚỦŨỤƯỪỨỬỮỰVWXYZ0123456789.,"

#define LANGUAGE "vie"

TesseractOCR::TesseractOCR()
{
    qDebug() << "TesseractOCR created";
}

TesseractOCR::~TesseractOCR()
{

}

void TesseractOCR::run()
{
    // TODO: Load image to a matrix
    // TODO: Binary
    // TODO: Hough transform
    // TODO: Segmentation

    //Mat img = imread("TEST_010.PNG", CV_LOAD_IMAGE_GRAYSCALE);
    Ptr<OCRTesseract> ocr = OCRTesseract::create(NULL, LANGUAGE, WHITE_LIST);
    string output;
    vector<Rect> boxes;
    vector<string> words;
    vector<float> confidences;

    ocr->run(mImgInput, output, &boxes, &words, &confidences, OCR_LEVEL_WORD);
    // Post processing
    for(uint16_t i=0; i<words.size(); ++i)
    {
        words[i] = correct(words[i]);
    }
    //TODO : gen outputpath
    //mTxtOutput = genTxtPath();
    for(uint16_t i=0; i<words.size(); ++i)
    {
        writeStrToTxt(mTxtOutput, words[i]);
        writeStrToTxt(mTxtOutput, " ");
    }
    qDebug() << "Tesseract done";
}
