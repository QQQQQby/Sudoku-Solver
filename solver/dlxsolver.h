#ifndef DLXSOLVER_H
#define DLXSOLVER_H

#include "solver.h"

class DlxSolver : public Solver {
public:
    DlxSolver(Sudoku *sudoku);
    Sudoku *getSolvedSudoku() override;

private:
    Sudoku *solvedSudoku;
};

#endif // DLXSOLVER_H
