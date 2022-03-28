#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>

MainWindow::MainWindow(QWidget *parent)
	:QMainWindow(parent),
	ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    /*
    int id = ui->stackedWidget->currentIndex();
    std::cout<<id<<std::endl;

    QStackedWidget *pages = ui->stackedWidget;
    int num  = pages->count();
    std::cout<<num<<std::endl;
    */

    //index:0 page 1
    //index:1 page 2
    //ui->stackedWidget->setCurrentIndex(1);



    //ADD USER CODE HERE
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}


void MainWindow::on_pushButton_5_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_12_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_11_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}


void MainWindow::on_pushButton_15_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void MainWindow::on_pushButton_13_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

