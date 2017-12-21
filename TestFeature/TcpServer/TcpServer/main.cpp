#include <iostream>
#include "tcpsocket.h"
using namespace std;



int main()
{
    cout << "Hello World!" << endl;
    TcpSocket::file_t file;
    file.header.type = TcpSocket::TXT_FILE;
    file.header.size = 10;
    TcpSocket::genFilePath(file, DOWNLOAD_FOLDER);
    TcpSocket::checkAvailableToWrite(file);
    return 0;
}
