#include"win2048.h"
#include <iostream>
void win2048::show() {
	for (int i = 0; i < gameboard.getdimension(); i++) {
		for (int j = 0; j < gameboard.getdimension(); j++) {
			Point t1 = { 100 * i,100 * j };
			if (gameboard.gettile(i, j) == NULL) {
				images[i][j] = new Image{ t1,"./picture/null.bmp" };
			}
			else {
				string picture = "./picture/" + std::to_string(gameboard.gettile(i, j)->getvalue()) + ".bmp";
				images[i][j] = new Image{ t1,picture };
			}
			canvas.attach(*images[i][j]);
		}

	}
	redraw();
	score.put(std::to_string(gameboard.getscore()));
}

win2048::win2048()
	:Window{ 400,500,"2048" },
	gameboard{ 4 },
	start{ "start",[this] {gameboard.reset(); is_start = 1; show();  } },
	quit{ "quit",Exit },
	W{ "W",[this] {if (is_start) { gameboard.move(Game::Direction::UP); show(); }} },
	A{ "A",[this] {if (is_start) { gameboard.move(Game::Direction::LEFT); show(); }} },
	S{ "S",[this] {if (is_start) { gameboard.move(Game::Direction::DOWN); show(); }} },
	D{ "D",[this] {if (is_start) { gameboard.move(Game::Direction::RIGHT); show(); }} },
	score{ "" },
	result{ "" }
{
	images.resize(4, vector<Image*>(4));
	div("vert<weight=100 <widgets gap=10 grid=[8,1] margin=10>>"
		"<canvas >");
	place("widgets", start);
	place("widgets", quit);
	place("widgets", W);
	place("widgets", A);
	place("widgets", S);
	place("widgets", D);
	place("widgets", score);
	place("widgets", result);
	place("canvas", canvas);
	collocate();
	set_keyboard_callback([this](const Keyboard_event& evt) {keyboard_cb(evt); });
}

void win2048::keyboard_cb(const Keyboard_event& evt)
{
	if ((evt.evt_code == event_code::key_press) && is_start)
	{
		char key = evt.key;
		switch (key)
		{
		case 'W':
		case '&':
			gameboard.move(Game::Direction::UP);	break;
		case 'A':
		case '%':
			gameboard.move(Game::Direction::LEFT);	break;
		case 'S':
		case '(':
			gameboard.move(Game::Direction::DOWN);	break;
		case 'D':
		case '\'':
			gameboard.move(Game::Direction::RIGHT);	break;
		default:
			break;
		}
		show();
	}
}

win2048::~win2048() {
	for (int i = 0; i < gameboard.getdimension(); i++)
		for (int j = 0; j < gameboard.getdimension(); j++) {
			delete images[i][j];
		}
}
int main() {
	win2048 win;
	gui_main(win);
}
