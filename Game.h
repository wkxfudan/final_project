#ifndef     GAME
#define     GAME
#include    <iostream>
#include    <vector>
#include    "ChessBoard.h"


class Game
{
private:
    ChessBoard oneboard;
public:
    enum class GameState{Start, Playing, GameOver, Win};
    GameState state;
    Game();
    ~Game();
    void restart();     //开始或重新开始*******************
    GameState CheckOver();    //检查游戏是否结束，如果有2048则结束，如果没有可移动的机会也结束，修改游戏状态并返回
    bool Combine(const char& input); //进行合并，如果合并有效返回True，合并无效则返回False*******************
    
    
};

Game::Game()
{
    restart();
}

Game::~Game()
{
}

#endif