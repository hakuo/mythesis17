#include "OCR.h"
#include <fstream>
#include <stdio.h>
#include <hunspell/hunspell.hxx>
#include "TCP/TcpUtils/TcpUtils.h"
#include <QDebug>

OCR::OCR()
{

}


OCR::~OCR()
{

}

void OCR::setInput(const std::string filepath, cv::Mat image)
{
    mImgInput = image;
    mFileName = basename(filepath.c_str());
}

std::string OCR::getOutput()
{
    return mTxtOutput;
}

bool OCR::writeStrToTxt(const std::string filepath, std::string src)
{
    std::ofstream output;
    output.open(filepath, std::ios::app);
    if(output.is_open())
    {
        output << src;
        output.close();
        return true;
    }
    return false;
}

bool OCR::readTxtToStr(const std::string filepath, std::string &des)
{
    std::string line;
    des.clear();
    std::ifstream input;
    input.open(filepath, std::ios::in);
    if(input.is_open())
    {
        while (std::getline(input, line)) {
            des = line;
            des += "\n";
        }
        input.close();
        return true;
    }
    return false;
}

void OCR::genOutputPath()
{
    mTxtOutput.clear();
    TcpUtils::createDirectory(UPLOAD_FOLDER);
    mTxtOutput = UPLOAD_FOLDER;
    mTxtOutput += mFileName;
    mTxtOutput += ".txt";
    remove(mTxtOutput.c_str());
}

std::string OCR::correct(std::string word)
{
    Hunspell hun ("/usr/share/hunspell/vi_VN.aff", "/usr/share/hunspell/vi_VN.dic");
    std::vector<std::string> suggestion;
    if(hun.spell(word, NULL, NULL) == 0)
    {
        qDebug() << "Spelling Error: " << word.c_str();
        suggestion = hun.suggest(word.c_str());
        if(suggestion.size() == 0)
        {
            qDebug() << "Can't find any suggestion for this word " << word.c_str();
            // return word
        }
        else
        {
            qDebug() << "Autocorrect: " << word.c_str() << " to " << suggestion[0].c_str();
            return suggestion[0];
        }
    }
    else
    {
        qDebug() << "Correct spelling" << word.c_str();
        // return word
    }
    return word;
}
