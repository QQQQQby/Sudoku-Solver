#include "game.h"

Game::Game(){
    board = new int*[9];
    for(int i = 0; i < 9; ++i){
        board[i] = new int[9];
        for(int j = 0; j < 9; ++j)
            board[i][j] = board[i][j];
    }
}

int Game::get(int i, int j){
    if(i < 0 || i >= 9 || j < 0 || j >= 9)
        throw "Out of range";
    return board[i][j];
}

void Game::set(int i, int j, int num){
    if(i < 0 || i >= 9 || j < 0 || j >= 9 || num < 1 || num > 9)
        throw "Out of range";
    for(int k = 0; k < 9; ++k){
        if(k != j && board[i][k] == num)
            throw "Invalid number";
        if(k != i && board[k][j] == num)
            throw "Invalid number";
    }
    for(int ii = i/3*3; ii < (i/3+1)*3; ++ii)
        for(int jj = j/3*3; jj < (j/3+1)*3; ++jj)
            if(board[ii][jj] == num && ii != i && jj != j)
                throw "Invalid number";
    board[i][j] = num;
}
