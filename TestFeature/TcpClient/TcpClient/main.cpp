#include <iostream>
#include "TcpUtils/TcpUtils.h"

using namespace std;

int main()
{
    string filepath1 = "/home/cuongdh8/file.ac.png";
    string filepath2 = "/home/cuongdh8/file.ac.PNG1";
    if(TcpUtils::compareStringInsensitive(TcpUtils::getFileExt(filepath1), TcpUtils::getFileExt(filepath2)))
    {
        std::cout << "Equal" << std::endl;
    }
    else
    {
        std::cout << "not equal" << std::endl;
    }
    return 0;
}
