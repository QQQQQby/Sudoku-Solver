#include "gameframe.h"
#include "solver/dfssolver.h"

#include <QEvent>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QPainter>
#include <QPen>
#include <QColor>
#include <QInputDialog>
#include <QMessageBox>
#include <QString>


int GameFrame::BORDER_WIDTH = 7;
int GameFrame::NORMAL_LINE_WIDTH = 3;
QFont GameFrame::NUMBER_FONT = QFont("Times New Romans", 20);

GameFrame::GameFrame(QWidget *parent) : QFrame(parent) {
    sudoku = new Sudoku();
    solvedSudoku = nullptr;

    currPos = QPoint(-1, -1);
    pressedCoord = QPoint(-1, -1);

}

GameFrame::~GameFrame() {
    delete sudoku;
    delete solvedSudoku;
}

void GameFrame::leaveEvent(QEvent *) {
    currPos = QPoint(-1, -1);
    repaint();
}

void GameFrame::mouseMoveEvent(QMouseEvent *event) {
    currPos = event->pos();
    repaint();
}

void GameFrame::mousePressEvent(QMouseEvent *event) {
    QPoint pos = event->pos();
    int *xs = getXs(), *ys = getYs();
    pressedCoord = getCoord(pos.x(), pos.y(), xs, ys);
    delete[] xs;
    delete[] ys;
    repaint();
}

void GameFrame::mouseReleaseEvent(QMouseEvent *event) {
    if (pressedCoord.x() == -1 || pressedCoord.y() == -1)
        return;

    int *xs = getXs(), *ys = getYs();
    QPoint pos = event->pos();
    QPoint clickedCoord = getCoord(pos.x(), pos.y(), xs, ys);
    int i = clickedCoord.x(), j = clickedCoord.y();
    if (clickedCoord == pressedCoord) {
        try {
            int num = QInputDialog::getInt(this, "", "");
            if (num < -1 || num > 9)
                throw "Out of range!";
            if (num != 0 && sudoku->get(i, j) != num) {
                sudoku->set(i, j, num);
                if (solvedSudoku != nullptr && solvedSudoku->get(i, j) != num) {
                    delete solvedSudoku;
                    solvedSudoku = nullptr;
                }
            }
        } catch (const char *s) {
            QMessageBox::warning(this, "Error", s);
        }
    }
    pressedCoord = QPoint(-1, -1);
    delete[] xs;
    delete[] ys;
    repaint();
}

void GameFrame::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    QPen pen;

    // Draw lines
    int *xs = getXs(), *ys = getYs();
    pen.setColor(Qt::black);
    for (int i = 0; i < 10; ++i) {
        if (i % 3 == 0)
            pen.setWidth(BORDER_WIDTH);
        else
            pen.setWidth(NORMAL_LINE_WIDTH);
        painter.setPen(pen);

        painter.drawLine(xs[i], BORDER_WIDTH / 2, xs[i], height() - 1 - BORDER_WIDTH / 2);
        painter.drawLine(BORDER_WIDTH / 2, ys[i], width() - 1 - BORDER_WIDTH / 2, ys[i]);
    }

    // Draw original blocks
    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    painter.setFont(NUMBER_FONT);
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (sudoku->get(i, j) != -1)
                painter.fillRect(calcRect(i, j, xs, ys), Qt::gray);

    // Draw the selected block
    QPoint drawCoord;
    if (currPos.x() != -1 && currPos.y() != -1) {
        if (pressedCoord.x() != -1 && pressedCoord.y() != -1) {
            drawCoord = pressedCoord;
            pen.setColor(QColor(0, 0, 150));
        } else {
            drawCoord = getCoord(currPos.x(), currPos.y(), xs, ys);
            pen.setColor(QColor(0, 0, 255));
        }

        if (drawCoord.x() != -1 && drawCoord.y() != -1) {
            pen.setWidth(1);
            painter.setPen(pen);
            painter.fillRect(calcRect(drawCoord.x(), drawCoord.y(), xs, ys), pen.color());
        }
    }

    // Draw numbers
    pen.setWidth(1);
    pen.setColor(Qt::black);
    painter.setPen(pen);
    for (int i = 0; i < 9; ++i) {
        for (int j = 0; j < 9; ++j) {
            int num = sudoku->get(i, j);
            if (num != -1)
                painter.drawText(calcRect(i, j, xs, ys), Qt::AlignCenter, QString::number(num));
        }
    }

    // Draw solved numbers
    if (solvedSudoku == nullptr)
        return;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (sudoku->get(i, j) == -1)
                painter.drawText(calcRect(i, j, xs, ys), Qt::AlignCenter, QString::number(solvedSudoku->get(i, j)));

    delete[] xs;
    delete[] ys;
}

int *GameFrame::getXs() {
    int *ans = new int[10];
    for (int row = 0; row < 10; ++row)
        ans[row] = row * (height() - BORDER_WIDTH) / 9 + BORDER_WIDTH / 2;
    return ans;
}

int *GameFrame::getYs() {
    int *ans = new int[10];
    for (int col = 0; col < 10; ++col)
        ans[col] = col * (width() - BORDER_WIDTH) / 9 + BORDER_WIDTH / 2;
    return ans;
}

QPoint GameFrame::getCoord(int x, int y, int *xs, int *ys) {
    if (xs == nullptr)
        xs = getXs();
    if (ys == nullptr)
        ys = getYs();

    for (int i = 0; i < 9; ++i)
        if (xs[i] == x || ys[i] == y)
            return QPoint(-1, -1);

    int row = -1, col = -1;
    for (int i = 0; i < 9; ++i) {
        if (xs[i] < x && x < xs[i + 1]) {
            col = i;
            break;
        }
    }
    for (int j = 0; j < 9; ++j) {
        if (ys[j] < y && y < ys[j + 1]) {
            row = j;
            break;
        }
    }
    return QPoint(row, col);
}

QRect GameFrame::calcRect(int row, int col, int *xs, int *ys) {
    if (xs == nullptr)
        xs = getXs();
    if (ys == nullptr)
        ys = getYs();

    int x1 = xs[col], y1 = ys[row], x2 = xs[col + 1], y2 = ys[row + 1];
    if (col % 3 == 0)
        x1 += BORDER_WIDTH / 2 + 1;
    else
        x1 += NORMAL_LINE_WIDTH / 2 + 1;
    if (row % 3 == 0)
        y1 += BORDER_WIDTH / 2 + 1;
    else
        y1 += NORMAL_LINE_WIDTH / 2 + 1;

    if ((col + 1) % 3 == 0)
        x2 -= BORDER_WIDTH / 2;
    else
        x2 -= NORMAL_LINE_WIDTH / 2;
    if ((row + 1) % 3 == 0)
        y2 -= BORDER_WIDTH / 2;
    else
        y2 -= NORMAL_LINE_WIDTH / 2;
    return QRect(x1, y1, x2 - x1, y2 - y1);
}

void GameFrame::solve() {
    if (solvedSudoku != nullptr)
        return;
    try {
        solvedSudoku = DfsSolver(sudoku).getSolvedSudoku();
    } catch (const char *s) {
        QMessageBox::warning(this, "Error", s);
    }
    repaint();
}
