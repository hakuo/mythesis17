#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

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

void MainWindow::on_imgBrowseButton_released()
{
    QString filename = QFileDialog::getOpenFileName(this, "Open File", "/home/cuongdh8", "Image File (*.png *.jpg);; All file (*.*)");
    if(!filename.isNull() && mImgProc.loadImage(filename.toStdString()))
    {
        ui->lineImgPath->setText(filename);
        showImage(ui->imgShow, mImgProc.mImageGray);
    }
    else
    {
        QMessageBox::critical(this, "Error", "Invalid input !");
    }

}

void MainWindow::showImage(QLabel *imgWin, cv::Mat img)
{
    return imgWin->setPixmap(QPixmap::fromImage(QImage(img.data, img.cols, img.rows, img.step, QImage::Format_RGB888)).scaled(imgWin->width(), imgWin->height(), Qt::KeepAspectRatio));

}
