#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "imageprocessing.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_imgBrowseButton_released();

private:
    Ui::MainWindow *ui;
    ImageProcessing mImgProc;

    void showImage(QLabel* imgWin, cv::Mat img);
};

#endif // MAINWINDOW_H
