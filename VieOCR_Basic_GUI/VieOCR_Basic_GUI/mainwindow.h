#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ocr/imageprocessing.h"
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

    void on_OCRButton_released();

    void on_postprocButton_released();

    void on_TTSButton_released();

    void on_autoButton_released();

private:
    Ui::MainWindow *ui;
    ImageProcessing mImgProc;

    training_feature_t getTrainingFeature();
};

#endif // MAINWINDOW_H
