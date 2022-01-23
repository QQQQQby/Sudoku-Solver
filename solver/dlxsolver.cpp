#include "dlxsolver.h"

#include <utils/dlx.h>

DlxSolver::DlxSolver(Sudoku *sudoku) {
    vector<vector<int>> mat, posList;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (sudoku->get(i, j) == 0){
                for (int k = 1; k <= 9; ++k){
                    mat.push_back(calcLine(i, j, k));
                    posList.push_back({i, j, k});
                }
            }else{
                mat.push_back(calcLine(i, j, sudoku->get(i, j)));
                posList.push_back({i, j, sudoku->get(i, j)});
            }

    vector<int> lineIds = Dlx(mat).getLineIds();
    if (lineIds.size() != 81)
        throw "Unsolvable!";
    solvedSudoku = new Sudoku;

    for (int id : lineIds)
        solvedSudoku->set(posList[id][0], posList[id][1], posList[id][2]);
}

Sudoku *DlxSolver::getSolvedSudoku() {
    return solvedSudoku;
}

vector<int> DlxSolver::calcLine(int i, int j, int num) {
    vector<int> ans(324, 0);
    ans[i * 9 + j] = 1;
    ans[i * 9 + num - 1 + 81] = 1;
    ans[j * 9 + num - 1 + 162] = 1;
    ans[(i / 3 * 3 + j / 3) * 9 + num - 1 + 243] = 1;
    return ans;
}
