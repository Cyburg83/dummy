//#include <QtWidgets>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "gamewidgets.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_4,SIGNAL(clicked()),this,SLOT(close()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
 //das kann gelöscht werden
}

void MainWindow::on_spinBox_valueChanged(int arg1)
{

}

void MainWindow::on_pushButton_clicked()
{

}
