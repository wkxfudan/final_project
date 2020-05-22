#include"win2048.h"
void win2048::show() {
	for (int i = 0; i < chessboard.getdimension(); i++) {
		for (int j = 0; j < chessboard.getdimension(); j++) {
			Point t1 = { 100 * i,100 * j };
			if (chessboard.gettile(i, j) == NULL) {
				images[i][j] = new Image{ t1,"./picture/null.bmp" };
			}
			else {
				string picture = "./picture/"+std::to_string(chessboard.gettile(i, j)->getvalue()) + ".bmp";
				images[i][j] = new Image{ t1,picture };
			}
			canvas.attach(*images[i][j]);
		}

	}
	redraw();
	score.put(std::to_string(chessboard.getscore()));
}

win2048::win2048()
	:Window{400,500,"2048"},
	chessboard{4},
	start{ "start",[this] {chessboard.reset(); is_start = 1; show();  } },
	quit{"quit",Exit},
	W{ "W",[this] {if (is_start) { chessboard.move(Game::Direction::UP); show(); }} },
	A{ "A",[this] {if (is_start) { chessboard.move(Game::Direction::LEFT); show(); }} },
	S{ "S",[this] {if (is_start) { chessboard.move(Game::Direction::DOWN); show(); }} },
	D{ "D",[this] {if (is_start) { chessboard.move(Game::Direction::RIGHT); show(); }} },
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
}
win2048::~win2048() {
	for(int i=0;i<chessboard.getdimension();i++)
		for (int j = 0; j < chessboard.getdimension(); j++) {
			delete images[i][j];
		}
}
int main() {
	win2048 win;
	gui_main(win);
}