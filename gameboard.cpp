#include "gameboard.h"

void Game::ChessBoard::handlecollision(int i, int j)
{
	board[i][j]->upgrade();
	board[i][j]->setflag(true);
	score += board[i][j]->getvalue();
}

void Game::ChessBoard::flaginit()
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			if(board[i][j]!=NULL)
				board[i][j]->setflag(false);
	collisionflag = false;
	moveflag = false;
}

bool Game::ChessBoard::checkwin() const
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			if (board[i][j]!=NULL)
				if(board[i][j]->getvalue()==2048)
				{
					std::cout << "game win" << std::endl;
					return true;
				}
	return false;
}

bool Game::ChessBoard::checklose() const
{
	if (full())
		if (!movePossible())
		{
			std::cout << "gamefailed" << std::endl;
			return true;
		}
	return false;
}

Game::ChessBoard::ChessBoard(int dim)
{
	dimension = dim;
	score = 0;
	collisionflag = false;
	moveflag = false;
	initial();
}

Game::ChessBoard::ChessBoard(const ChessBoard& other)
{
	dimension = other.dimension;
	initial();
	for (int i = 0; i < dimension; ++i)
		for (int j = 0; j < dimension; ++j) 
		{
			if (other.board[i][j] == NULL)
				board[i][j] = NULL;
			else
				board[i][j] = new tile(*(other.board[i][j]));
		}
}

Game::ChessBoard::~ChessBoard()
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			delete board[i][j];
}

void Game::ChessBoard::reset()
{
	srand((int)time(0));
	initial();
	for (int i = 0; i < 2; i++)
	{
		std::pair<int, int> freepos = freeposition();
		tile* newtile = new tile((rand() % 2 + 1) * 2);
		board[freepos.first][freepos.second] = newtile;
	}
}

void Game::ChessBoard::move(Direction dir)
{
	flaginit();
	switch (dir)
	{
	case Game::UP:
		for (int i = 0; i < dimension; i++)
			for (int j = 0; j < dimension; j++)
				moveup(i, j);
		break;
	case Game::DOWN:
		for (int i = 0; i < dimension; i++)
			for (int j = dimension - 1; j >= 0; j--)
				movedown(i, j);
		break;
	case Game::LEFT:
		for (int j = 0; j < dimension; j++)
			for (int i = 0; i < dimension; i++)
				moveleft(i, j);
		break;
	case Game::RIGHT:
		for (int j = 0; j < dimension; j++)
			for (int i = dimension - 1; i >= 0; i--)
				moveright(i, j);
		break;
	default:
		break;
	}
	if (!full())
	{
		std::pair<int, int> freepos = freeposition();
		srand((int)time(0));
		tile* newtile = new tile((rand() % 2 + 1) * 2);
		board[freepos.first][freepos.second] = newtile;
	}
	checkwin();
	checklose();
}

void Game::ChessBoard::print() const
{
	for (int j = 0; j < dimension; j++)
	{
		for (int i = 0; i < dimension; i++)
			if (board[i][j] == NULL)
				std::cout << " " << " ";
			else
				std::cout << board[i][j]->getvalue() << " ";
		std::cout << "\n";
	}
}

bool Game::ChessBoard::full() const
{
	for (int i = 0; i < dimension; i++)
		for (int j = 0; j < dimension; j++)
			if (board[i][j] == NULL)
				return false;
	return true;
}

std::pair<int, int> Game::ChessBoard::freeposition() const
{
	std::pair<int, int> pos;
	srand((int)time(0));
	do
	{
		pos.first = rand() % dimension;
		pos.second = rand() % dimension;
	} while (board[pos.first][pos.second] != NULL);
	return pos;
}

bool Game::ChessBoard::movePossible() const
{
	ChessBoard cb = ChessBoard(*this);
	cb.move(LEFT);
	if (cb.moveflag == true)
		return true;
	cb.move(RIGHT);
	if (cb.moveflag == true)
		return true;
	cb.move(UP);
	if (cb.moveflag == true)
		return true;
	cb.move(DOWN);
	if (cb.moveflag == true)
		return true;
	cb.~ChessBoard();
	return false;
}

void Game::ChessBoard::initial()
{
	board.resize(dimension);
	for (int i = 0; i < dimension; ++i)
		board[i].resize(dimension);
	for (int i = 0; i < dimension; ++i)
		for (int j = 0; j < dimension; ++j)
			board[i][j] = NULL;
}

void Game::ChessBoard::movedown(int i, int j)
{
	bool combinflag = false;
	if (board[i][j] == NULL)
		return;
	if (j == dimension - 1)//已经处于边缘处
		return;

	int newj = j + 1;
	while (newj < dimension)
	{
		if (board[i][newj] != NULL)
			break;
		newj++;
	}
	if (newj != dimension)//找到相邻项
	{
		if (*board[i][j] == *board[i][newj])
		{
			handlecollision(i, newj);//合并处理
			collisionflag = true;
			combinflag = true;
		}
		else
		{
			board[i][newj - 1] = board[i][j];//不能合并移到相邻项前一格
		}
	}
	else
	{
		board[i][dimension - 1] = board[i][j];//无相邻项移到边缘
	}
	if (newj - 1 != j || combinflag)
	{
		moveflag = true;
		board[i][j] = NULL;//原位置删除
	}
}

void Game::ChessBoard::moveup(int i, int j)
{
	bool combinflag=false;
	if (board[i][j] == NULL)
		return;
	if (j == 0)
		return;

	int newj = j - 1;
	while (newj >= 0)
	{
		if (board[i][newj] != NULL)
			break;
		newj--;
	}
	if (newj != -1)
	{
		if (*board[i][j] == *board[i][newj])
		{
			handlecollision(i, newj);
			collisionflag = true;
			combinflag = true;
		}
		else
		{
			board[i][newj + 1] = board[i][j];
		}
	}
	else
	{
		board[i][0] = board[i][j];
	}

	if (newj + 1 != j || combinflag)
	{
		moveflag = true;
		board[i][j] = NULL;
	}
}

void Game::ChessBoard::moveleft(int i, int j)
{
	bool combinflag = false;
	if (board[i][j] == NULL)
		return;
	if (i == 0)
		return;;
	int newi = i - 1;
	while (newi >= 0)
	{
		if (board[newi][j] != NULL)
			break;
		newi--;
	}
	if (newi != -1)
	{
		if (*board[i][j] == *board[newi][j])
		{
			handlecollision(newi, j);
			collisionflag = true;
			combinflag = true;
		}
		else
		{
			board[newi + 1][j] = board[i][j];
		}
	}
	else
	{
		board[0][j] = board[i][j];
	}

	if (newi + 1 != i || combinflag)
	{
		moveflag = true;
		board[i][j] = NULL;
	}
}

void Game::ChessBoard::moveright(int i, int j)
{
	bool combinflag = false;
	if (board[i][j] == NULL)
		return;
	if (i == dimension - 1)
		return;
	 
	int newi = i + 1;
	while (newi <dimension)
	{
		if (board[newi][j] != NULL)
			break;
		newi++;
	}
	if (newi != dimension)
	{
		if (*board[i][j] == *board[newi][j])
		{
			handlecollision(newi, j);
			collisionflag = true;
			combinflag = true;
		}
		else
		{
			board[newi - 1][j] = board[i][j];
		}
	}
	else
	{
		board[dimension - 1][j] = board[i][j];
	}

	if (newi - 1 != i || combinflag)
	{
		moveflag = true;
		board[i][j] = NULL;
	}
}
