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
#include "../utils/socket.h"

class OCRMgr {
public:
    OCRMgr();
    virtual ~OCRMgr();

    void run();
    void stop();
private:
    static OCRMgr* m_me;

    /* Define member variable*/
    DLTool* pDLTool;
    OCRTool* pOCRTool;
    TTSTool* pTTSTool;
    pthread_t mOCRMgrThead;
    volatile bool mTerminateServer;

    /* Create OCRMgr_Server to receive msg from DLTool, OCRTool, TTSTool */
    bool readyToRun();
    static void* OCRMgrThread(void* arg);
    void startOCRMgrServer();

};

#endif /* OCRMGR_H_ */
