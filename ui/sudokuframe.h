#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include<QFrame>

#include <game/sudoku.h>

class SudokuFrame : public QFrame {
    Q_OBJECT

public:
    SudokuFrame(QWidget *parent = nullptr);
    ~SudokuFrame();

protected:
    void leaveEvent(QEvent *);
    void mouseMoveEvent(QMouseEvent *);
    void mousePressEvent(QMouseEvent *);
    void mouseReleaseEvent(QMouseEvent *);
    void paintEvent(QPaintEvent *);

private:
    Sudoku *sudoku, *solvedSudoku;
    QPoint currPos, pressedCoord;

    int *getXs();
    int *getYs();

    QPoint getCoord(int, int, int * = nullptr, int * = nullptr);
    QRect calcRect(int, int, int * = nullptr, int * = nullptr);

    static int BORDER_WIDTH, NORMAL_LINE_WIDTH;
    static QFont NUMBER_FONT;

public slots:
    void solve();
};

#endif // GAMEFRAME_H
