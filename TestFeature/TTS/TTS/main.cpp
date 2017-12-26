#include <iostream>
#include <stdlib.h>
#include <TTS.h>
using namespace std;

int main()
{
    setenv("TTS_SYS_ROOT", "/home/cuongdh8/workspace/qt/cpp/mythesis17/VieOCR_Basic_GUI", 1);
    iHearTech::TTS test;
    test.sayText("20-04-1995");
    return 0;
}
