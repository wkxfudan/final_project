#pragma once
#include "tile.h"
#include<iostream>
#include<vector>
#include<utility>
#include<cstdlib>
#include<ctime>

namespace Game {

	enum Direction { UP, DOWN, LEFT, RIGHT };

	class ChessBoard {
	private:
		std::vector<std::vector<tile*>> board;//左下格为(0,0)
		int dimension;
		int score;
		bool collisionflag;
		bool moveflag;

		void initial();//棋盘初始化

		void moveup(int i, int j);//移动某一方块
		void movedown(int i, int j);
		void moveleft(int i, int j);
		void moveright(int i, int j);

		void handlecollision(int i, int j);//合并处理

		void flaginit();//每次移动前对合并标记初始化
		std::pair<int, int> freeposition() const;//获得一个随机空位置信息
		bool full() const;
		bool movePossible() const;



	public:
		ChessBoard(int dim);
		ChessBoard(const ChessBoard& other);
		~ChessBoard();

		void reset();

		tile* gettile(int i, int j) { return board[i][j]; };
		int getdimension() const { return dimension; };
		int getscore() const { return score; }

		void move(Direction dir);
		void print() const;
		bool lastcollisionflag() const { return collisionflag; };//合并是否发生

		bool checkwin() const;
		bool checklose() const;

	};

}