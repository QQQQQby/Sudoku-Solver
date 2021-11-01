#ifndef DLX_H
#define DLX_H

#include "dlxnode.h"

#include <vector>
using namespace std;

class Dlx {
public:
    explicit Dlx(vector<vector<int>>);
    ~Dlx();
    vector<int> getLineIds();

private:
    size_t m, n;
    int *colCounts;
    DlxNode *head;
    DlxNode **colHeads;
    DlxNode ***matNodes;
    vector<int> lineIds;

    bool dfsSolve();
    static void check(vector<vector<int>>);
    void remove(DlxNode *);
    void recover(DlxNode *);
};

#endif // DLX_H
