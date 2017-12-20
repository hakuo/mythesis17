#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "ocr/ocrfactory.h"

/////////////////////////////// Utilities /////////////////////////////////////
namespace Utility {
void showImage(QLabel *imgWin, cv::Mat img)
{
    //return imgWin->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)).scaled(imgWin->width(), imgWin->height(), Qt::KeepAspectRatio));
    QImage qImg;
    cv::Mat RGBImg;
    if(img.channels()==3)
    {
        cv::cvtColor(img, RGBImg, CV_BGR2RGB);
        qImg=QImage(RGBImg.data,RGBImg.cols,RGBImg.rows,QImage::Format_RGB888);
    }
    else if(img.channels()==1)
    {
        qImg=QImage(img.data,img.cols,img.rows,QImage::Format_Indexed8);
    }
    else {
        return;
    }
    imgWin->setPixmap(QPixmap::fromImage(qImg).scaled(imgWin->width(), imgWin->height(), Qt::KeepAspectRatio));
}
}

/////////////////////////// MAIN WINDOWS ////////////////////////////
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->statusBar->showMessage("Status");
}

MainWindow::~MainWindow()
{
    delete ui;
}

training_feature_t MainWindow::getTrainingFeature()
{
    training_feature_t ret;
    ret.value=0;
    if(ui->groupBox->isEnabled())
    {
        ret.Zoning=(ui->zoningCheckBox->isChecked())?1:0;
        ret.Distance=(ui->distanceCheckBox->isChecked())?1:0;
        ret.Crossing=(ui->crossingCheckBox->isChecked())?1:0;
    }
    return ret;
}





/////////////////////////////// Event handlers ///////////////////////////////

void MainWindow::on_imgBrowseButton_released()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home/cuongdh8", "Image File (*.png *.jpg);; All file (*.*)");
    if(!filename.isNull() && mImgProc.loadImage(filename.toStdString()))
    {
        ui->lineImgPath->setText(filename);
        Utility::showImage(ui->imgShow, mImgProc.mImageGray);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Invalid input !");
    }

}


void MainWindow::on_preprocButton_released()
{

}

void MainWindow::on_extWordButton_released()
{

}

void MainWindow::on_extCharButton_released()
{

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    ui->groupBox->setDisabled(index!=0);
}

void MainWindow::on_OCRButton_released()
{
    OCR* ocr_tool = OCRFactory::Get()->createOCR((OCR::ocr_type_t)ui->comboBox->currentIndex());
    delete ocr_tool;
}

void MainWindow::on_postprocButton_released()
{

}

void MainWindow::on_TTSButton_released()
{

}

void MainWindow::on_autoButton_released()
{

}
