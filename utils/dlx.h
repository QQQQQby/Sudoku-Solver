#ifndef DLX_H
#define DLX_H

#include "dlxnode.h"

#include <vector>
using namespace std;

class Dlx {
public:
    Dlx(int **, int, int);
    ~Dlx();
    vector<int>* getLineIds();

private:
    int m, n;
    int *colCounts;
    DlxNode *head;
    DlxNode **colHeads;
    DlxNode ***matNodes;
    vector<int>* lineIds;

    bool dfsSolve();
};

#endif // DLX_H
