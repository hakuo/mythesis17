#include "image_processing_util.h"

#define IMAGE_PATH "../../data/VIE_001.png"


void startOCRTool() {
    Mat img;
    loadImage(img, IMAGE_PATH);
    cvtImgToBin(img, ADAPTIVE_THRESHOLD_GAUSSIAN);
    showImage(img, "HelloWorld");
}

int main(int argc, char *argv[]) {
    startOCRTool();
    return 0;
}
























