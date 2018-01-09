#include "OCR.h"
#include <opencv2/opencv.hpp>
#include <fstream>
#include <stdio.h>
#include <hunspell/hunspell.hxx>
#include "TCP/TcpUtils/TcpUtils.h"
#include <stdlib.h>

#define HUNSPELL_DIR "/hunspell"

OCR::OCR()
{
    resetPath();
    OCR_SYS_ROOT = std::string(getenv("TOOL_SYS_ROOT"));
    std::cout << "OCR created" << std::endl;
}


OCR::~OCR()
{

}

std::string OCR::createTxt(std::string inputPath)
{
    std::string ret = "";
    cv::Mat tmp;
    if(this->loadImage(tmp, inputPath))   // TODO: loadImage, preprocessing
    {
        this->setInputPath(inputPath);
        this->setImgInput(tmp);
        this->genTxtPath(mTxtOutput, mInputPath);
        this->run();
        while(isRun);
        ret = getOutput();
        resetPath();
    }
    return ret;
}

void OCR::setImgInput(cv::Mat img)
{
    mImgInput = img.clone();
}

void OCR::deSkew(cv::Mat &cropped, cv::Mat image)
{
    double angle;
    cv::Mat bin, element, rot_mat, rotated;
    cv::threshold(image, bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    //invert color
    cv::bitwise_not(bin, bin);
    element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(2,1));
    cv::erode(bin, bin, element);
    std::vector<cv::Point> points;
    cv::Mat_<uchar>::iterator it = bin.begin<uchar>();
    cv::Mat_<uchar>::iterator end = bin.end<uchar>();
    for(; it!= end; ++it)
    {
        if(*it) points.push_back(it.pos()); // find white points
    }
    cv::RotatedRect box = minAreaRect(cv::Mat(points));
    cv::Size box_size = box.size;

    if(box.angle < -45.) std::swap(box_size.width, box_size.height);

    angle = box.angle;
    if(angle < -45.) angle += 90;
    std::cout << "Input File angle: " << angle << std::endl;

    //     draw rectangle box
    //     Point2f vertices[4];
    //     box.points(vertices);
    //     for(int i=0; i<4; ++i)
    //        line(bin, vertices[i], vertices[(i+1)%4], Scalar(255, 0, 0), 1, CV_AA);

    rot_mat = cv::getRotationMatrix2D(box.center, angle, 1);
    cv::warpAffine(image, rotated, rot_mat, bin.size(), cv::INTER_CUBIC);

    //     crop text box
    cv::getRectSubPix(rotated, box_size, box.center, cropped);
    //    cv::namedWindow("Original", cv::WINDOW_AUTOSIZE);
    //    cv::namedWindow("Rotated", cv::WINDOW_AUTOSIZE);
    //    cv::namedWindow("Cropped", cv::WINDOW_AUTOSIZE);
    //    cv::imshow("Original", bin);
    //    cv::imshow("Rotated", rotated);
    //    cv::imshow("Cropped", cropped);
    cv::waitKey();
}

void OCR::lineSegment(std::vector<cv::Mat> &lineArray, cv::Mat image)
{
    // binary
    cv::Mat bin;
    cv::threshold(image, bin, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    cv::bitwise_not(bin, bin);
    cv::Mat1f horProj;
    cv::reduce(bin, horProj, 1, CV_REDUCE_AVG);
    float th = 0;
    cv::Mat1b hist = (horProj <= th);

    // Get mean coordinate of white white pixels groups
    std::vector<int> ycoords;
    int y = 0;
    int count = 0;
    bool isSpace = false;
    for (int i = 0; i < bin.rows; ++i)
    {
        if (!isSpace)
        {
            if (hist(i))
            {
                isSpace = true;
                count = 1;
                y = i;
            }
        }
        else
        {
            if (!hist(i))
            {
                isSpace = false;
                ycoords.push_back(y / count);
            }
            else
            {
                y += i;
                count++;
            }
        }
    }

    // Draw line as final result
    cv::Mat3b result;
    cv::cvtColor(image, result, cv::COLOR_GRAY2BGR);
    cv::Mat croppedLine;
    int curr_line = 0;
    for (size_t i = 0; i < ycoords.size(); ++i)
    {
        //line(result, cv::Point(0, ycoords[i]), cv::Point(result.cols, ycoords[i]), cv::Scalar(0, 255, 0));
        croppedLine = image(cv::Rect(0, curr_line, image.cols, ycoords[i] - curr_line));
        curr_line = ycoords[i];
        lineArray.push_back(croppedLine);
        //cv::imshow("line", croppedLine);
        //cv::waitKey();
    }
    croppedLine = image(cv::Rect(0, curr_line, image.cols, image.rows - curr_line));
    lineArray.push_back(croppedLine);
    //cv::imshow("line", croppedLine);
    //cv::waitKey();
    //cv::namedWindow("lineDetection", cv::WINDOW_NORMAL);
    //cv::imshow("lineDetection", result);
    //cv::waitKey();
}

void OCR::setInputPath(std::string str)
{
    mInputPath = str;
}



// loadImg from image path
// if load success => store imagePath to storeStr and store image
bool OCR::loadImage(cv::Mat &image, const std::string imagePath)
{
    image = cv::imread(imagePath, CV_LOAD_IMAGE_GRAYSCALE);
    return (image.data == NULL) ? false : true;
}

std::string OCR::getOutput()
{
    return mTxtOutput;
}

// write a string to txt in append mode
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
            des += line;
            des += "\n";
        }
        input.close();
        return true;
    }
    return false;
}

// Input: Path to input file (*.jpg)
// Output: Path to output file (*.txt)
// Generate output filname with the same name
// IMG_0001.jpg => IMG_0001.txt

void OCR::genTxtPath(std::string &txtOutStr, std::string filepath)
{
    std::string outDir = OCR_SYS_ROOT + TMP_PATH;
    std::string filename = basename(filepath.c_str());          // abc.jpg
    if(!TcpUtils::checkDirExist(outDir.c_str()))
    {
        TcpUtils::createDirectory(outDir.c_str());
    }
    txtOutStr = outDir + "/" +TcpUtils::removeExt(filename) + ".txt";    // <outDir>/abc.txt
    remove(txtOutStr.c_str());
}

void OCR::resetPath()
{
    mInputPath = "";
    mTxtOutput = "";
    //mImgInput.release();
}

std::string OCR::correct(std::string word)
{
    std::string hunPath1 = OCR_SYS_ROOT + HUNSPELL_DIR + "/vi_VN.aff";
    std::string hunPath2 = OCR_SYS_ROOT + HUNSPELL_DIR + "/vi_VN.dic";
    Hunspell hun(hunPath1.c_str(), hunPath2.c_str());
    std::vector<std::string> suggestion;
    if(hun.spell(word, NULL, NULL) == 0)
    {
        std::cout << "Spelling Error: " << word.c_str() << std::endl;
        suggestion = hun.suggest(word.c_str());
        if(suggestion.size() == 0)
        {
            std::cout << "Can't find any suggestion for this word " << word.c_str() << std::endl;
            // return word
        }
        else
        {
            std::cout << "Autocorrect: " << word.c_str() << " to " << suggestion[0].c_str() << std::endl;
            return suggestion[0];
        }
    }
    else
    {
        std::cout << "Correct spelling" << word.c_str() << std::endl;
        // return word
    }
    return word;
}
