#include <iostream>
#include "tcpsocket.h"
using namespace std;

typedef struct
{
    char c;
    int i;
} mstruct;

int main()
{
    cout << "Hello World!" << endl;

    cout << "sizeof(tcp_pkg_t): " << (int)sizeof(TcpSocket::tcp_pkg_t) << endl;
    cout << "sizeof(mstruct)" << int(sizeof(mstruct)) << endl;
    return 0;
}
