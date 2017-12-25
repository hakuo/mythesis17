#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "OCR/OCR_Factory.h"
#include "TTS/TTS.h"
#include "TCP/TcpUtils/TcpUtils.h"

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

void MainWindow::on_dataBrowseButton_released()
{
    QString foldername = QFileDialog::getExistingDirectory(this, "Open TTS Database", QDir::currentPath());
    if(!foldername.isNull()) { ui->lineDataPath->setText(foldername); }
}

void MainWindow::on_OCRButton_released()
{
    OCR* ocr_tool = OCRFactory::Get()->createOCR((OCR::ocr_type_t)ui->comboBox->currentIndex());
    ocr_tool->setInput(ui->lineImgPath->text().toStdString(), mImgProc.mImageGray);
    ui->statusBar->showMessage("OCR processing...");
    ocr_tool->run();
    ui->statusBar->showMessage("OCR done !");
    std::string outStr;
    ocr_tool->readTxtToStr(ocr_tool->getOutput(), outStr);
    ui->textOutput->setText(QString::fromStdString(outStr));
    delete ocr_tool;
}

void MainWindow::on_TTSButton_released()
{
    // set environment path first
    std::string database = ui->lineDataPath->text().toStdString();
    if((database == "") || (TcpUtils::checkDirExist(database.c_str()) == false))
    {
        QMessageBox::critical(this, "Error", "Invalid database path");
        return;
    }
    setenv("TTS_SYS_ROOT", database.c_str(), 1);

}

void MainWindow::on_autoButton_released()
{

}


