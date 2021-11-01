#include "dlx.h"

#include <vector>

Dlx::Dlx(vector<vector<int>> mat) {
    check(mat);

    m = mat.size();
    n = mat[0].size();

    // Initialize nodes
    head = new DlxNode();
    colHeads = new DlxNode *[n];
    colCounts = new int[n];
    for (size_t j = 0; j < n; ++j) {
        colHeads[j] = new DlxNode(-1, (int) j);
        colCounts[j] = 0;
    }

    matNodes = new DlxNode **[m];
    for (size_t i = 0; i < m; ++i) {
        matNodes[i] = new DlxNode *[n];
        for (size_t j = 0; j < n; ++j) {
            if (mat[i][j] == 1) {
                matNodes[i][j] = new DlxNode((int) i, (int) j);
                ++colCounts[j];
            } else {
                matNodes[i][j] = nullptr;
            }
        }
    }

    // Link all the heads
    head->linkRight(colHeads[0]);
    colHeads[n - 1]->linkRight(head);
    for (size_t j = 0; j < n - 1; ++j)
        colHeads[j]->linkRight(colHeads[j + 1]);

    // Link the rest rows
    for (size_t i = 0; i < m; ++i) {
        size_t j;
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
    for (size_t j = 0; j < n; ++j) {
        DlxNode *first = colHeads[j], *prev = first;
        for (size_t i = 0; i < m; ++i) {
            if (matNodes[i][j] != nullptr) {
                prev->linkDown(matNodes[i][j]);
                prev = matNodes[i][j];
            }
        }
        prev->linkDown(first);
    }

    dfsSolve();
}

Dlx::~Dlx() {
    for (size_t i = 0; i < m; ++i) {
        for (size_t j = 0; j < n; ++j)
            delete matNodes[i][j];
        delete[] matNodes[i];
    }
    delete[] matNodes;
    for (size_t j = 0; j < n; ++j)
        delete colHeads[j];
    delete[] colHeads;
    delete[] colCounts;
    delete head;
}

vector<int> Dlx::getLineIds() {
    return lineIds;
}

bool Dlx::dfsSolve() {
    if (head->right == head)
        return true;

    DlxNode *chosenHead = head->right;
    for (DlxNode *p = chosenHead->right; p != head; p = p->right)
        if (colCounts[p->col] < colCounts[chosenHead->col])
            chosenHead = p;
    if (colCounts[chosenHead->col] < 1)
        return false;

    vector<DlxNode *> colNodes;
    for (DlxNode *p = chosenHead->down; p != chosenHead; p = p->down)
        colNodes.push_back(p);
    if (colNodes.empty())
        return false;

    vector<vector<DlxNode *>> sameRowNodes;
    for (DlxNode *p : colNodes) {
        vector<DlxNode *> currRowNodes;
        for (DlxNode *q = p->right; q != p; q = q->right)
            currRowNodes.push_back(q);
        sameRowNodes.push_back(currRowNodes);
    }

    // Remove nodes
    remove(chosenHead);
    for (DlxNode *p : colNodes)
        remove(p);
    for (const vector<DlxNode *> &nodes : sameRowNodes)
        for (DlxNode *p : nodes)
            remove(p);

    for (size_t i = 0; i < colNodes.size(); ++i) {
        // Remove some nodes if we chose one line
        vector<DlxNode *> otherNodes;
        for (DlxNode *p : sameRowNodes[i]) {
            DlxNode *q = colHeads[p->col];
            size_t k = otherNodes.size();
            for (DlxNode *r = q->down; r != q; r = r->down) {
                otherNodes.push_back(r);
                for (DlxNode *s = r->right; s != r; s = s->right)
                    otherNodes.push_back(s);
            }
            for (auto it = otherNodes.begin() + k; it != otherNodes.end(); ++it)
                remove(*it);
        }
        for (DlxNode *p : sameRowNodes[i])
            remove(colHeads[p->col]);

        // Run Depth-First Search
        lineIds.push_back(colNodes[i]->row);
        if (dfsSolve())
            return true;
        lineIds.pop_back();

        // Recover nodes
        for (auto it = sameRowNodes[i].rbegin(); it != sameRowNodes[i].rend(); ++it)
            recover(colHeads[(*it)->col]);
        for (auto it = otherNodes.rbegin(); it != otherNodes.rend(); ++it)
            recover(*it);
    }

    // Recover nodes
    for (auto rowIt = sameRowNodes.rbegin(); rowIt != sameRowNodes.rend(); ++rowIt)
        for (auto it = rowIt->rbegin(); it != rowIt->rend(); ++it)
            recover(*it);
    for (auto it = colNodes.rbegin(); it != colNodes.rend(); ++it)
        recover(*it);
    recover(chosenHead);
    return false;
}

void Dlx::check(vector<vector<int>> mat) {
    size_t m = mat.size();
    if (m == 0)
        throw "invalid_argument";
    size_t n = mat[0].size();
    if (n == 0)
        throw "invalid_argument";
    for (size_t i = 0; i < m; ++i) {
        if (mat[i].size() != n)
            throw "invalid_argument";
        for (size_t j = 0; j < n; ++j)
            if (mat[i][j] != 0 && mat[i][j] != 1)
                throw "invalid_argument";
    }
}

void Dlx::remove(DlxNode *p) {
    p->remove();
    --colCounts[p->col];
}

void Dlx::recover(DlxNode *p) {
    p->recover();
    colCounts[p->col] += 1;
}
