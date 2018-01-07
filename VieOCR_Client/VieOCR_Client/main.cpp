#include <iostream>
#include "Task/Task.h"

using namespace std;

int main()
{
    setenv("TOOL_SYS_ROOT", "/home/cuongdh8/workspace/qt/cpp/mythesis17/VieOCR_Client", 1);
    Task *pTask = new Task();
    pTask->initParameter(TCP_PORT, 1, 1, "192.168.1.38");
    pTask->runAllTask();
    cout << "Client is running... Enter 'c' to capture or 'e' to exit" << endl;

    // Block program here
    char input;
    while (true)
    {
        input = getchar();
        if('e' == input)
        {
            break;
        }

        if('c' == input)
        {
            pTask->capture();
        }
    }

    pTask->stopAllTask();
    delete pTask;
    return 0;
}


