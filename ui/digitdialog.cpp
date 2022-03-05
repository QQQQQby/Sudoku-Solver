#include "digitdialog.h"
#include "ui_digitdialog.h"

DigitDialog::DigitDialog(QWidget *parent)
        : QDialog(parent), ui(new Ui::DigitDialog) {
    ui->setupUi(this);
    setWindowTitle("Select digit");
    setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    selected = -1;

    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(selectOne()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(selectTwo()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(selectThree()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(selectFour()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(selectFive()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(selectSix()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(selectSeven()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(selectEight()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(selectNine()));
    connect(ui->pushButton_clear, SIGNAL(clicked()), this, SLOT(clear()));
}

DigitDialog::~DigitDialog() {
    delete ui;
}

int DigitDialog::getSelected(){
    return selected;
}

void DigitDialog::selectOne(){
    selected = 1;
    accept();
}

void DigitDialog::selectTwo(){
    selected = 2;
    accept();
}

void DigitDialog::selectThree(){
    selected = 3;
    accept();
}

void DigitDialog::selectFour(){
    selected = 4;
    accept();
}

void DigitDialog::selectFive(){
    selected = 5;
    accept();
}

void DigitDialog::selectSix(){
    selected = 6;
    accept();
}

void DigitDialog::selectSeven(){
    selected = 7;
    accept();
}

void DigitDialog::selectEight(){
    selected = 8;
    accept();
}

void DigitDialog::selectNine(){
    selected = 9;
    accept();
}

void DigitDialog::clear(){
    selected = 0;
    accept();
}
