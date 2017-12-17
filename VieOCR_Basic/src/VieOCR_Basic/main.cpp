#include <iostream>
#include "ocr.h"

using namespace std;

int main()
{
    OCR test;
    test.loadImage("../sample_test/TEST_001.PNG");
    test.showImageRGB("TEST_001.PNG");
    test.cvtRGB2Bin();
    test.showImageBin("TEST_001_Bin.PNG");
    waitKey();
    cout << "Hello World!" << endl;
    return 0;
}
