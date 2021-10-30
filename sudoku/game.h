#ifndef GAME_H
#define GAME_H


class Game
{
public:
    Game();
    int get(int, int);
    void set(int, int, int);
private:
    int** board;
};

#endif // GAME_H
