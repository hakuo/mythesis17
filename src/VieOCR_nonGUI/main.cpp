#include "image_processing_util.h"

#define IMAGE_PATH "../../data/VIE_001.png"



int main(int argc, char *argv[]) {
    Mat img;
    loadImage(img, IMAGE_PATH);
    showImage(img, "HelloWorld");
    return 0;
}
























