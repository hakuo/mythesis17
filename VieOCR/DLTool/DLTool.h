/*
 * DLTool.h
 *
 *  Created on: Nov 23, 2017
 *      Author: cuongdh8
 */

#ifndef DLTOOL_H_
#define DLTOOL_H_

#include <sys/socket.h>
#include <mqueue.h>

class DLTool {
public:
    DLTool();
    virtual ~DLTool();

    void init();
    void run();
    void stop();
private:
    int readyToRun();

};

#endif /* DLTOOL_H_ */
