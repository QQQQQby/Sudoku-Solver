#ifndef DFSSOLVER_H
#define DFSSOLVER_H

#include "solver.h"

#include <vector>
#include <utility>

using namespace std;

class DfsSolver : public Solver {
public:
    DfsSolver(Sudoku *sudoku);
    Sudoku *getSolvedSudoku() override;

private:
    Sudoku *solvedSudoku;
    bool dfs(size_t, vector <pair<int, int>>);
};

#endif // DFSSOLVER_H
