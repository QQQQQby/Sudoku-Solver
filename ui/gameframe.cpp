#include "gameframe.h"

#include <QMessageBox>

GameFrame::GameFrame(QWidget* parent) : QFrame(parent)
{

}

GameFrame::~GameFrame()
{
    delete game;
}

void GameFrame::solve()
{
    QMessageBox::information(nullptr, "123", "456");
}
