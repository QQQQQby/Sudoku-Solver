#include "dlx.h"

#include <vector>

Dlx::Dlx(int **mat, int m, int n) {
    if (m <= 0 || n <= 0)
        throw "Invalid arguments.";
    this->m = m;
    this->n = n;
    head = new DlxNode();

    colHeads = new DlxNode *[n];
    colCounts = new int[n];
    for (int j = 0; j < n; ++j) {
        colHeads[j] = new DlxNode(-1, j);
        colCounts[j] = 0;
    }

    matNodes = new DlxNode **[m];
    for (int i = 0; i < m; ++i) {
        matNodes[i] = new DlxNode *[n];
        for (int j = 0; j < n; ++j) {
            if (mat[i][j] == 1) {
                matNodes[i][j] = new DlxNode(i, j);
                ++colCounts[j];
            } else {
                matNodes[i][j] = nullptr;
            }
        }
    }

    // Link all the heads
    head->linkRight(colHeads[0]);
    colHeads[n - 1]->linkRight(head);
    for (int j = 0; j < n; ++j)
        colHeads[j]->linkRight(colHeads[j + 1]);

    // Link the rest rows
    for (int i = 0; i < m; ++i) {
        int j;
        for (j = 0; j < n && matNodes[i][j] == nullptr; ++j);

        if (j == n)
            continue;

        DlxNode *first = matNodes[i][j], *prev = first;
        for (++j; j < n; ++j) {
            if (matNodes[i][j] != nullptr) {
                prev->linkRight(matNodes[i][j]);
                prev = matNodes[i][j];
            }
        }
        prev->linkRight(first);
    }

    // Link all the columns
    for (int j = 0; j < n; ++j) {
        DlxNode *first = colHeads[j], *prev = first;
        for (int i = 0; i < m; ++i) {
            if (matNodes[i][j] != nullptr) {
                prev->linkDown(matNodes[i][j]);
                prev = matNodes[i][j];
            }
        }
        prev->linkDown(first);
    }

    lineIds = new vector<int>;
    dfsSolve();
}

Dlx::~Dlx() {
    for (int i = 0; i < m; ++i) {
        for (int j = 0; j < n; ++j)
            delete matNodes[i][j];
        delete[] matNodes[i];
    }
    for (int j = 0; j < n; ++j)
        delete colHeads[j];
    delete[] matNodes;
    delete[] colHeads;
    delete[] colCounts;
    delete head;
}

vector<int> *Dlx::getLineIds() {
    return lineIds;
}

bool Dlx::dfsSolve() {
    if (head->right == head)
        return true;
    DlxNode *p = head->right, *chosenHead = p;
    while (p != head) {
        if (colCounts[p->col] < colCounts[chosenHead->col])
            chosenHead = p;
        p = p->right;
    }
    if (colCounts[chosenHead->col] < 1)
        return false;

    // TODO
}
