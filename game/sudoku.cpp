#include "game/sudoku.h"

Sudoku::Sudoku() {
    board = new int *[9];
    for (int i = 0; i < 9; ++i) {
        board[i] = new int[9];
        for (int j = 0; j < 9; ++j)
            board[i][j] = -1;
    }
}

int Sudoku::get(int i, int j) {
    if (i < 0 || i >= 9 || j < 0 || j >= 9)
        throw "Out of range";
    return board[i][j];
}

void Sudoku::set(int i, int j, int val) {
    if (i < 0 || i >= 9 || j < 0 || j >= 9)
        throw "Out of range";
    if (val == -1) {
        board[i][j] = -1;
        return;
    }
    if (val < 1 || val > 9)
        throw "value out of range";
    for (int k = 0; k < 9; ++k) {
        if (k != j && board[i][k] == val)
            throw "Invalid number";
        if (k != i && board[k][j] == val)
            throw "Invalid number";
    }
    for (int ii = i / 3 * 3; ii < (i / 3 + 1) * 3; ++ii)
        for (int jj = j / 3 * 3; jj < (j / 3 + 1) * 3; ++jj)
            if (board[ii][jj] == val && ii != i && jj != j)
                throw "Invalid number";
    board[i][j] = val;
}
