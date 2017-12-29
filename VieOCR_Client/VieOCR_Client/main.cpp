#include <iostream>
#include <ConsoleMenu.h>


using namespace std;

void HelloWorld()
{
    cout << "Hello World" << endl;
}


int main()
{
    bool running = true;
    do {
//        ConsoleMenu menu("What should this program do?\n", "Invalid operation; ", "> ", {
//                             {"1", [&running] {
//                                  running = true;
//                              }},
//                             {"2", HelloWorld},
//                             {"e", [&running] {
//                                  running = false;
//                              }}
//                         });
//        menu();
    } while (running);
}


