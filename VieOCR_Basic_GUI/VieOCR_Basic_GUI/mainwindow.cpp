#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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

void MainWindow::on_browseButton_released()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "/home/cuongdh8/", "Images (*.png *.xpm *.jpg)");
    //if(!fileName.isNull()) ui->linePath->setText(fileName);


}
