#ifndef DLXNODE_H
#define DLXNODE_H


class DlxNode {
public:
    DlxNode *up, *down, *left, *right;
    int row, col;

    explicit DlxNode(int row = -1, int col = -1);
    void remove();
    void recover();
    void linkDown(DlxNode *);
    void linkRight(DlxNode *);

private:
    DlxNode *upOri, *downOri, *leftOri, *rightOri;
};

#endif // DLXNODE_H
