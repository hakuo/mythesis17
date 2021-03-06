/*
 * TTS.h
 *
 *  Created on: Jul 1, 2015
 *      Author: messier
 */

#ifndef TTS_H_
#define TTS_H_
#include <string>
#include <stdio.h>
#include "TTS_Utils/TextObjectTTS.h"
#include "TTS_Utils/TextObjectTTS.h"
#include "TTS_Utils/UnitSelector.h"
#include "common.h"
#define TTS_OUTPUT_PATH "/database/tts"

namespace iHearTech {

class TTS {
public:
    TTS();
    virtual ~TTS();
    void sayText(const char* text);
    void sayUrl(const char* url);
    void sayUrl(const std::string url);
    void sayFile(const char *file_path);
    void sayFile(const std::string file_path);
    void sayFile(FILE *pFile);
    std::string createWav(const char *file_path);
    void outputUnresolvedList(std::string file_path);
    void enableUnresolvedList(bool enable);
    bool play_enable;
private:
    iHearTech::UnitSelector *unit_sel;
    iHearTech::TextObjectTTS *text_obj;
    std::string TTS_SYS_ROOT;
};

} /* namespace iHearTech */

#endif /* TTS_H_ */
