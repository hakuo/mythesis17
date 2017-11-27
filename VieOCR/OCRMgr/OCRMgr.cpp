/*
 * OCRMgr.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#include "OCRMgr.h"

OCRMgr::OCRMgr() {
    pDLTool = new DLTool();
    pOCRTool = new OCRTool();
    pTTSTool = new TTSTool();
}

OCRMgr::~OCRMgr() {
    /* Stop all thread */
    stop();

    /* delete all pointers */
    if(pDLTool) {
        delete pDLTool;
        pDLTool = NULL;
    }

    if(pOCRTool) {
        delete pOCRTool;
        pOCRTool = NULL;
    }

    if(pTTSTool) {
        delete pTTSTool;
        pTTSTool = NULL;
    }
}

/*
 * @function: readyToRun
 * @brief: Check pDLTool, pOCRTool, pTTSTool has been initialized or not
 * @parameter: void
 * @return: READY/NOT READY    TRUE/FALSE
 */
bool OCRMgr::readyToRun() {
    if(pDLTool) {
        pDLTool->run();
    }
    if(pOCRTool) {
        pOCRTool->run();
    }
    if(pTTSTool) {
        pTTSTool->run();
    }
    return (pDLTool && pOCRTool && pTTSTool);
}

void OCRMgr::threadLoop() {
    message_t msg;
    if(pDLTool->popTxQueue(msg)) {
        pOCRTool->pushRxQueue(msg);
    }
    if(pOCRTool->popTxQueue(msg)) {
        pTTSTool->pushRxQueue(msg);
    }
    if(pTTSTool->popTxQueue(msg)) {
        pDLTool->pushRxQueue(msg);
    }
}
