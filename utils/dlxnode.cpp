#include "dlxnode.h"

DlxNode::DlxNode(int row, int col) {
    this->row = row;
    this->col = col;

    up = nullptr;
    down = nullptr;
    left = nullptr;
    right = nullptr;

    upOri = nullptr;
    downOri = nullptr;
    leftOri = nullptr;
    rightOri = nullptr;
}

void DlxNode::remove() {
    upOri = up;
    downOri = down;
    leftOri = left;
    rightOri = right;

    up->down = down;
    down->up = up;
    left->right = right;
    right->left = left;
}

void DlxNode::recover() {
    upOri->down = this;
    downOri->up = this;
    leftOri->right = this;
    rightOri->left = this;
}

void DlxNode::linkDown(DlxNode *p) {
    this->down = p;
    p->up = this;
}

void DlxNode::linkRight(DlxNode *p) {
    this->right = p;
    p->left = this;
}
