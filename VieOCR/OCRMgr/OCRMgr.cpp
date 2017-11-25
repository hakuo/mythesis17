/*
 * OCRMgr.cpp
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#include "OCRMgr.h"

OCRMgr* OCRMgr::m_me = NULL;

OCRMgr::OCRMgr() {
    pDLTool = new DLTool();
    pOCRTool = new OCRTool();
    pTTSTool = new TTSTool();

    mOCRMgrThead = 0;
}

OCRMgr::~OCRMgr() {
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
 * @function: run
 * @brief: run OCR Manager application
 * @parameter: void
 * @return: void
 */
void OCRMgr::run() {
    if(readyToRun()) {
        if(pthread_create(&mOCRMgrThead, NULL, OCRMgr::OCRMgrThread, this) < 0) {
            perror("OCRTool cannot create thread");
        }
    }
}

void OCRMgr::stop() {

}

/*
 * @function: OCRMgrThread
 * @brief: create pointer to OCRMgrThread
 * @parameter: void*
 * @return: NULL
 */
void* OCRMgr::OCRMgrThread(void* arg) {
    m_me = reinterpret_cast<OCRMgr*> (arg);
    m_me->startOCRMgrServer();
    return NULL;
}

/*
 * @function: readyToRun
 * @brief: Check pDLTool, pOCRTool, pTTSTool has been initialized or not
 * @parameter: void
 * @return: READY/NOT READY    TRUE/FALSE
 */
bool OCRMgr::readyToRun() {
    return (pDLTool && pOCRTool && pTTSTool);
}

void OCRMgr::startOCRMgrServer() {

}










