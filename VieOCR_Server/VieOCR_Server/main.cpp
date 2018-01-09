#include <iostream>
#include "Task/Task.h"

using namespace std;

int main()
{
    std::string system_root = "/home/cuongdh8/workspace/qt/cpp/mythesis17/VieOCR_Server";
    setenv("TOOL_SYS_ROOT", system_root.c_str(), 1);
    Task *pTask = new Task(OCR::TESSERACT_OCR);
    pTask->initParameter(TCP_PORT, 1);
    pTask->runAllTask();

    //cout << "Server is running... Enter 'e' to exit" << endl;
    //Block program here
    char input;
    while (true) {
        cout << "Server is running... Enter 'e' to exit or 'a' to clean up tmp_dir" << endl;
        input = getchar();
        if('e' == input)
        {
            break;
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
