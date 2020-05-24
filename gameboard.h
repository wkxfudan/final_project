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
		std::vector<std::vector<tile*>> board;//���¸�Ϊ(0,0)
		int dimension;
		int score;
		bool collisionflag;
		bool moveflag;

		void initial();//���̳�ʼ��

		void moveup(int i, int j);//�ƶ�ĳһ����
		void movedown(int i, int j);
		void moveleft(int i, int j);
		void moveright(int i, int j);

		void handlecollision(int i, int j);//�ϲ�����

		void flaginit();//ÿ���ƶ�ǰ�Ժϲ���ǳ�ʼ��
		std::pair<int, int> freeposition() const;//���һ�������λ����Ϣ
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
		bool lastcollisionflag() const { return collisionflag; };//�ϲ��Ƿ���

		bool checkwin() const;
		bool checklose() const;

	};

}