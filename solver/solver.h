#ifndef BASESOLVER_H
#define BASESOLVER_H

#include "game/sudoku.h"

class Solver
{
public:
    virtual Sudoku *getSolvedSudoku() = 0;
};

#endif // BASESOLVER_H
