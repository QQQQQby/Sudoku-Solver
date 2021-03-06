#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QIcon>

MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    ui->sudokuFrame->setMouseTracking(true);
    setWindowTitle("Sudoku Solver");
    setWindowIcon(QIcon(":/icons/logo.ico"));

    connect(ui->solveButton, SIGNAL(clicked()), ui->sudokuFrame, SLOT(solve()));
    connect(ui->clearButton, SIGNAL(clicked()), ui->sudokuFrame, SLOT(clear()));
}

MainWindow::~MainWindow() {
    delete ui;
}

