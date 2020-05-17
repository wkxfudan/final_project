#ifndef     WIN2048
#define     WIN2048
//#include "Window.h"
#include "Game.h"

class Win2048 : public Window
{
private:
    Game chessgame;
    vector<Button* >  buttons;
    Canvas canvas;  //棋盘描绘
    Label display;  //文字显示
    /*自由发挥*/

    Button& create_button(char key);
    void key_pressed(char key);             
public:
    Win2048();
    ~Win2048();
};

Win2048::Win2048()
{
}

Win2048::~Win2048()
{
}



#endif