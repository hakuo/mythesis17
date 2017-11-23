/*
 * VieOCR_Main.cpp
 *
 *  Created on: Nov 22, 2017
 *      Author: cuongdh8
 */

#include "common.h"
#include "OCRTool/OCRTool.h"

int main()
{
    OCRTool a;
    std::string b;
    std::string c = "xxx.yyy";
    a.run(c, b);
    std::cout << b << std::endl;
    return 0;
}




