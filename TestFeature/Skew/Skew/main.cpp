#include <iostream>
#include <opencv2/opencv.hpp>

//using namespace std;
//using namespace cv;

void lineSegment(std::vector<cv::Mat> &lineArray, cv::Mat image)
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

void computeAngle(cv::Mat image, cv::Mat &cropped)
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

int main()
{
    double angle;
    const char* filename = "/home/cuongdh8/0002.jpg";
    cv::Mat img = cv::imread(filename, CV_LOAD_IMAGE_GRAYSCALE);
    cv::Mat cropped;
    std::vector<cv::Mat> lineArray;
    computeAngle(img, cropped);
    lineSegment(lineArray, cropped);
    return 0;
}
