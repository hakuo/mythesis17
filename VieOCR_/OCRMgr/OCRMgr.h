/*
 * OCRMgr.h
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#ifndef OCRMGR_H_
#define OCRMGR_H_

#include "../DLTool/DLTool.h"
#include "../OCRTool/OCRTool.h"
#include "../TTSTool/TTSTool.h"

class OCRMgr: public Thread {

public:
    OCRMgr();
    virtual ~OCRMgr();

private:
    /* Define member variable*/
    Thread *pDLTool = NULL;
    Thread *pOCRTool = NULL;
    Thread *pTTSTool = NULL;

    virtual bool readyToRun();
    virtual void threadLoop();
};

#endif /* OCRMGR_H_ */
