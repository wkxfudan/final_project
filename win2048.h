#pragma once
#include"GUI.h"
#include"window.h"
#include"final_project-chlrod-patch-1/gameboard.h"
using namespace Graph_lib;
class win2048 :public Window {
private:
	Canvas canvas;
	Button start, quit, W, A, S, D;
	Out_box score, result;
	Game::GameBoard gameboard;
	vector<vector<Image*>> images;
	void show();
	int is_start = 0;

	void keyboard_cb(const Keyboard_event& evt);//键盘事件函数
public:
	win2048();
	~win2048();
};
