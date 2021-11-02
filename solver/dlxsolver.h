#ifndef DLXSOLVER_H
#define DLXSOLVER_H

#include <vector>
using namespace std;

#include "solver.h"

class DlxSolver : public Solver {
public:
    DlxSolver(Sudoku *sudoku);
    Sudoku *getSolvedSudoku() override;

private:
    Sudoku *solvedSudoku;
    vector<int> calcLine(int, int, int);
};

#endif // DLXSOLVER_H
