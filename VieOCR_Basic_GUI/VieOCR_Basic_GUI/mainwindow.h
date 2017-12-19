#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLabel>
#include "imageprocessing.h"
#include "common.h"

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

    void on_preprocButton_released();

    void on_extWordButton_released();

    void on_extCharButton_released();

    void on_comboBox_currentIndexChanged(int index);

    void on_trainButton_released();

    void on_OCRButton_released();

    void on_postprocButton_released();

    void on_TTSButton_released();

    void on_autoButton_released();

private:
    Ui::MainWindow *ui;
    ImageProcessing mImgProc;

    void showImage(QLabel* imgWin, cv::Mat img);
    training_feature_t getTrainingFeature();
};

#endif // MAINWINDOW_H
