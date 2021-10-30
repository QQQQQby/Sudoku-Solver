#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->sudokuFrame->setMouseTracking(true);

    connect(ui->solveButton, SIGNAL(clicked()), ui->sudokuFrame, SLOT(solve()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

