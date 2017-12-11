/*
 * TTSTool.h
 *
 *  Created on: Nov 24, 2017
 *      Author: cuongdh8
 */

#ifndef TTSTOOL_H_
#define TTSTOOL_H_
#include "../common.h"
#include "../Thread/Thread.h"

class TTSTool: public Thread {
public:
    TTSTool();
    virtual ~TTSTool();

private:
    virtual bool readyToRun();
    virtual void threadLoop();
};

#endif /* TTSTOOL_H_ */
