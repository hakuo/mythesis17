/*
 * OCRTool.h
 *
 *  Created on: Nov 23, 2017
 *      Author: cuongdh8
 */

#ifndef OCRTOOL_H_
#define OCRTOOL_H_

#include "../common.h"
#include <opencv2/opencv.hpp>


class OCRTool {
public:
    OCRTool();
    virtual ~OCRTool();

    void run(std::string& imgPath, std::string& txtPath);
private:

};

#endif /* OCRTOOL_H_ */
