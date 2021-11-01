#include "dlx.h"

#include <vector>

Dlx::Dlx(vector<vector<int>>mat) {
    check(mat);
    this->m = mat.size();
    this->n = mat[0].size();
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
    for (size_t j = 0; j < n; ++j)
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
    for (size_t j = 0; j < n; ++j)
        delete colHeads[j];
    delete[] matNodes;
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
        DlxNode *q = p->right;
        vector<DlxNode *> currRowNodes;
        sameRowNodes.push_back(currRowNodes);
        while (q != p) {
            currRowNodes.push_back(q);
            q = q->right;
        }
    }

    // Remove nodes
    remove(chosenHead);
    for (DlxNode *p : colNodes)
        remove(p);
    for (const vector<DlxNode *>& nodes : sameRowNodes)
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
            for (size_t j = k; j < otherNodes.size(); ++j)
                remove(otherNodes[j]);
        }
        for (DlxNode *p : sameRowNodes[i])
            remove(colHeads[p->col]);

        // Run Depth-First Search
        lineIds.push_back(colNodes[i]->row);
        if (dfsSolve())
            return true;
        lineIds.pop_back();

        // Recover nodes
        for (size_t j = sameRowNodes[i].size() - 1; j >= 0; --j)
            recover(colHeads[sameRowNodes[i][j]->col]);
        for (size_t j = otherNodes.size() - 1; j >= 0; --j)
            recover(otherNodes[j]);
    }
    // Recover nodes
    for (size_t i = sameRowNodes.size() - 1; i >= 0; --i)
        for (size_t j = sameRowNodes[i].size() - 1; j >= 0; --j)
            recover(sameRowNodes[i][j]);
    for (size_t i = colNodes.size() - 1; i >= 0; --i)
        recover(colNodes[i]);
    recover(chosenHead);
    return false;
}

void Dlx::check(vector<vector<int>> mat) {
    size_t m = mat.size(), n = mat[0].size();
    for (size_t i = 0; i < m; ++i)
        for (size_t j = 0; j < n; ++j)
            if (mat[i][j] != 0 && mat[i][j] != 1)
                throw "invalid_argument";
}

void Dlx::remove(DlxNode *p) {
    p->remove();
    --colCounts[p->col];
}

void Dlx::recover(DlxNode *p) {
    p->recover();
    ++colCounts[p->col];
}
