#ifndef GAME_H
#define GAME_H

class Sudoku {
public:
    Sudoku();
    int get(int, int);
    void set(int, int, int);

private:
    int **board;
};

#endif // GAME_H
