#include "image_processing_util.h"

/*
 * @brief: load image from file
 * @param: image => output matrix
 * @param: filepath => path to the input file
 * @return: -1 => fail
 * @return: 0 => successful
 */

int loadImage(Mat& image, const char* filepath) {
    int ret = -1;
    image = imread(filepath, CV_LOAD_IMAGE_GRAYSCALE);
    if(image.data != NULL) {
        ret = 0;
    }
    return ret;
}

void showImage(Mat image, const char* title) {
    namedWindow(title, WINDOW_AUTOSIZE);    // Create window for display
    imshow(title, image);                   // Show image
    waitKey();                              // Wait for a keystroke in the window
}

/*
 * @brief: convert image from GRAY to BINARY
 *`@param: image => input/output image
 * @param: mode
 * @return: -1 => fail
 * @return: 0 => successful
 */

int cvtImgToBin(Mat& image, int mode) {
    int ret = -1;
    switch(mode) {
    case NORMAL_THRESHOLD:

        ret = 0;
        break;
    case ADAPTIVE_THRESHOLD_GAUSSIAN:
        adaptiveThreshold(image,                        /* Input image */
                          image,                        /* Output image */
                          255,                          /* maxValue */
                          ADAPTIVE_THRESH_GAUSSIAN_C,   /* adaptiveMethod */
                          CV_THRESH_BINARY,             /* thresholdType */
                          45,                           /* blockSize */
                          1                             /* C */
                          );
        ret = 0;
        break;
    case ADAPTIVE_THRESHOLD_MEAN:

        ret = 0;
        break;
    default: /* Failed case */
        break;
    }
    return ret;
}

/*
 * @brief: extract words from binary image
 * @param: input <= binary image
 * @param: output => array
 * @return: -1 => fail
 * @return: 0 => error
 */

int extractWord(Mat& image) {
    int ret;

    return ret;
}

/*
 * @brief:
 * @param:
 * @return:
 */
int extractCharacter(Mat& image) {
    int ret;

    return ret;
}















