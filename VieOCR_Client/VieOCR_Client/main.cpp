#include <iostream>
#include <ConsoleMenu.h>


using namespace std;

void start()
{
    cout << "start" << endl;
}


void capture()
{
    cout << "capture" << endl;
}

void setup_ip()
{
    cout << "setup_ip" << endl;
}

void send()
{
    cout << "send" << endl;
}

int main()
{
    bool running = true;
    do {
        ConsoleMenu menu("What should this program do?\n", "Invalid operation; ", "> ", {
                             {"start", start},
                             {"capture", capture},
                             {"setup_ip", setup_ip},
                             {"send", send},
                             {"exit", [&running] {
                                  running = false;
                              }}
                         });
        menu();
    } while (running);
}


