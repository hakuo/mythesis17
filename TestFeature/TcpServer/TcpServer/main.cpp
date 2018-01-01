#include <iostream>
#include "TcpServer/TcpServer.h"
using namespace std;



int main()
{
    TcpServerTask test;
    test.setListenPort(8080);
    test.setListenNum(1);
    if(test.readyToRun())
    {
        test.TaskHandler();
    }

    return 0;
}
