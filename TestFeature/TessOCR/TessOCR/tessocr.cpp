#include "tessocr.h"
#include "tesseract/include/text.hpp"
#include <opencv2/core/utility.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;
using namespace cv::text;
TessOCR::TessOCR()
{

}

TessOCR::~TessOCR()
{

}

void TessOCR::predict()
{
    // TODO: Load image to a matrix
    // TODO: Binary
    // TODO: Hough transform
    // TODO: Segmentation

    const char* white_list = "aàáảãạăằắẳẵặâầấẩẫậbcdđeèéẻẽẹêềếểễệfghiìíỉĩịjklmnoòóỏõọôồốổỗộơờớởỡợpqrstuùúủũụưừứửữựvwxyzAÀÁẢÃẠĂẰẮẲẴẶÂẦẤẨẪẬBCDĐEÈÉẺẼẸÊỀẾỂỄỆFGHIÌÍỈĨỊJKLMNOÒÓỎÕỌÔỒỐỔỖỘƠỜỚỞỠỢPQRSTUÙÚỦŨỤƯỪỨỬỮỰVWXYZ0123456789.,";
    Mat img = imread("TEST_010.PNG", CV_LOAD_IMAGE_GRAYSCALE);
    Ptr<OCRTesseract> ocr = OCRTesseract::create(NULL, "vie", white_list);
    string output;
    vector<Rect> boxes;
    vector<string> words;
    vector<float> confidences;

    ocr->run(img, output, &boxes, &words, &confidences, OCR_LEVEL_WORD);
    waitKey();


}
