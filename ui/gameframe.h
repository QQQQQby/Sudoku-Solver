#ifndef GAMEFRAME_H
#define GAMEFRAME_H

#include<QFrame>

#include <sudoku/game.h>

class GameFrame : public QFrame
{
    Q_OBJECT

public:
    GameFrame(QWidget* parent = nullptr);
    ~GameFrame();

public slots:
    void solve();

private:
    Game* game;
};

#endif // GAMEFRAME_H
