#include <iostream>
#include "tessocr.h"

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    TessOCR test;
    test.predict();
    return 0;
}
