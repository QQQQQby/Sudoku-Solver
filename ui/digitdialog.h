#ifndef DIGITDIALOG_H
#define DIGITDIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class DigitDialog; }
QT_END_NAMESPACE

class DigitDialog : public QDialog
{
    Q_OBJECT
public:
    explicit DigitDialog(QWidget *parent = 0);
    ~DigitDialog();
    int getSelected();

private:
    Ui::DigitDialog *ui;
    int selected;

private slots:
    void selectOne();
    void selectTwo();
    void selectThree();
    void selectFour();
    void selectFive();
    void selectSix();
    void selectSeven();
    void selectEight();
    void selectNine();
    void clear();
};

#endif // DIGITDIALOG_H
