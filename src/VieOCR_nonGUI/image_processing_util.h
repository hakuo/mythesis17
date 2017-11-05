#ifndef IMAGE_PROCESSING_UTIL_H
#define IMAGE_PROCESSING_UTIL_H

#include "common.h"
/* Define threshold mode */
enum {
    NORMAL_THRESHOLD,
    ADAPTIVE_THRESHOLD_MEAN,
    ADAPTIVE_THRESHOLD_GAUSSIAN
};


/* Define image processing ultility */
int loadImage(Mat& image, const char* filepath);
int cvtImgToBin(Mat& image, int mode);
void showImage(Mat image, const char* title);

#endif // IMAGE_PROCESSING_UTIL_H
