#include <iostream>
#include "Task/Task.h"

using namespace std;

int main()
{
    setenv("TOOL_SYS_ROOT", "/home/cuongdh8/workspace/qt/cpp/mythesis17/VieOCR_Server", 1);
    Task *pTask = new Task(OCR::TESSERACT_OCR);
    pTask->initParameter(8080, 1);
    pTask->runAllTask();

    cout << "Server is running... Enter 'e' to exit" << endl;
    //Block program here
    while (true) {
        if('e' == getchar())
        {
            break;
        }
    }
    delete pTask;
    return 0;
}
