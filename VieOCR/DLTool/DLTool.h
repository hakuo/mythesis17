/*
 * DLTool.h
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#ifndef DLTOOL_H_
#define DLTOOL_H_
#include "../common.h"
#include "../Thread/Thread.h"

class DLTool: public Thread {
public:
    DLTool();
    virtual ~DLTool();

private:
    virtual bool readyToRun();
    virtual void threadLoop();


};
#endif /* DLTOOL_H_ */
