#ifndef GAME_H
#define GAME_H

class Sudoku {
public:
    Sudoku();
    Sudoku(const Sudoku & that);
    ~Sudoku();
    int get(int, int);
    void set(int, int, int);

private:
    int **board;
};

#endif // GAME_H
