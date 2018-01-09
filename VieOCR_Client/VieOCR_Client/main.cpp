#include <iostream>
#include "Task/Task.h"

using namespace std;

int main()
{
    //setenv("TOOL_SYS_ROOT", "/home/cuongdh8/workspace/qt/cpp/mythesis17/VieOCR_Client", 1);
    std::string system_root = "/home/pi/workspace/mythesis17/VieOCR_Client";
    setenv("TOOL_SYS_ROOT", system_root.c_str(), 1);
    Task *pTask = new Task();
    pTask->initParameter(TCP_PORT, 1, 1, "192.168.1.38");
    pTask->runAllTask();
    // Block program here
    char input;
    while (true)
    {
        cout << "Client is running... Enter 'c' to capture or 'a' to clean up tmp_dir or 'e' to exit" << endl;
        input = getchar();
        if('e' == input)
        {
            break;
        }

        if('c' == input)
        {
            pTask->capture();
        }

        if('a' == input)
        {
            std::string cmd;
            cmd = "rm -rf " + system_root + TMP_PATH;
            system(cmd.c_str());
        }
    }

    pTask->stopAllTask();
    delete pTask;
    return 0;
}


