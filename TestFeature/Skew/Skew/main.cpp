#include <iostream>
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;

void lineDetection(Mat img);
double compute_skew(const char* filename);
void deskew(const char* filename, double angle);

double compute_skew(const char* filename)
{
    // Load in grayscale
    Mat img = imread(filename, 0);
    // Binarize
    threshold(img, img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
    // Invert colors
    bitwise_not(img, img);
    Mat element = getStructuringElement(MORPH_RECT, Size(2, 1));
    erode(img, img, element);
    vector<Point> points;
    Mat_<uchar>::iterator it = img.begin<uchar>();
    Mat_<uchar>::iterator end = img.end<uchar>();
    for(; it!= end; ++it)
    {
        if(*it) points.push_back(it.pos()); // find white points
    }
    RotatedRect box = minAreaRect(Mat(points));
    double angle = box.angle;
    if(angle < -45.) angle += 90;

    Point2f vertices[4];
    box.points(vertices);
    for(int i=0; i<4; ++i)
        line(img, vertices[i], vertices[(i+1)%4], Scalar(255, 0, 0), 1, CV_AA);

    cout << "File " << filename << ": " << angle << endl;
    return angle;
}

void deskew(const char* filename, double angle)
{
    Mat img = imread(filename, 0);
    bitwise_not(img, img);
    vector<Point> points;
    Mat_<uchar>::iterator it = img.begin<uchar>();
    Mat_<uchar>::iterator end = img.end<uchar>();
    for(; it!=end; ++it)
    {
        if(*it) points.push_back(it.pos());
    }
    RotatedRect box = minAreaRect(Mat(points));
    Mat rot_mat = getRotationMatrix2D(box.center, angle, 1);
    Mat rotated;
    warpAffine(img, rotated, rot_mat, img.size(), INTER_CUBIC);
    Size box_size = box.size;
    if(box.angle < -45.)
        swap(box_size.width, box_size.height);
    Mat cropped;
    getRectSubPix(rotated, box_size, box.center, cropped);
    namedWindow("Original", WINDOW_AUTOSIZE);
    namedWindow("Rotated", WINDOW_AUTOSIZE);
    namedWindow("Cropped", WINDOW_AUTOSIZE);
    imshow("Original", img);
    imshow("Rotated", rotated);
    imshow("Cropped", cropped);
    lineDetection(cropped);
    waitKey();
}

void lineDetection(Mat img)
{
    img = img > 200;
    Mat1f horProj;
    reduce(img, horProj, 1, CV_REDUCE_AVG);
    float th = 0;
    Mat1b hist = (horProj <= th);

    // Get mean coordinate of white white pixels groups
    vector<int> ycoords;
    int y = 0;
    int count = 0;
    bool isSpace = false;
    for (int i = 0; i < img.rows; ++i)
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
    Mat3b result;
    cvtColor(img, result, COLOR_GRAY2BGR);
    for (size_t i = 0; i < ycoords.size(); ++i)
    {
        line(result, Point(0, ycoords[i]), Point(result.cols, ycoords[i]), Scalar(0, 255, 0));
    }
    imshow("lineDetection", result);
    waitKey();

}

int main()
{
    double angle;
    const char* filename = "/home/cuongdh8/Downloads/IMG_test/IMG_00045.jpg";
    angle = compute_skew(filename);
    deskew(filename, angle);
    return 0;
}
