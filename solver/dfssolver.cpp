#include "dfssolver.h"

#include <vector>
#include <utility>

using namespace std;

DfsSolver::DfsSolver(Sudoku *sudoku) {
    if (sudoku == nullptr)
        throw "Sudoku is null!";

    vector <pair<int, int>> zeroCoords;
    for (int i = 0; i < 9; ++i)
        for (int j = 0; j < 9; ++j)
            if (sudoku->get(i, j) == 0)
                zeroCoords.push_back(make_pair(i, j));

    solvedSudoku = new Sudoku(*sudoku);
    if (!dfs(0, zeroCoords))
        throw "Unsolvable";
}

Sudoku *DfsSolver::getSolvedSudoku() {
    return solvedSudoku;
}

bool DfsSolver::dfs(size_t idx, vector <pair<int, int>> zeroCoords) {
    if (idx == zeroCoords.size())
        return true;

    pair<int, int> coord = zeroCoords.at(idx);
    bool *flags = new bool[9];
    for (int i = 0; i < 9; ++i)
        flags[i] = true;

    for (int i = 0; i < 9; ++i) {
        if (solvedSudoku->get(coord.first, i) != 0)
            flags[solvedSudoku->get(coord.first, i) - 1] = false;
        if (solvedSudoku->get(i, coord.second) != 0)
            flags[solvedSudoku->get(i, coord.second) - 1] = false;
    }
    int ii = coord.first / 3 * 3, jj = coord.second / 3 * 3;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (solvedSudoku->get(ii + i, jj + j) != 0)
                flags[solvedSudoku->get(ii + i, jj + j) - 1] = false;

    for (int i = 0; i < 9; ++i) {
        if (flags[i]) {
            solvedSudoku->set(coord.first, coord.second, i + 1);
            if (dfs(idx + 1, zeroCoords)) {
                delete[] flags;
                return true;
            }
        }
    }
    solvedSudoku->set(coord.first, coord.second, 0);
    delete[] flags;
    return false;
}
