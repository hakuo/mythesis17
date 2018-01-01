#include <iostream>
#include "TcpClient/TcpClient.h"

using namespace std;

int main()
{
    TcpClient test;
    test.setDefaultInterface("wlpSSSS8s0");
    test.connectToServer("127.0.0.1", 8080);
    test.sendFile("aaa.txt");
    test.closeSock();
    return 0;
}
