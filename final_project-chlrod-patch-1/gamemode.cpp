#include"gameboard.h"
#include"tile.h"

int main()
{
	Game::ChessBoard cb = Game::ChessBoard(4);
	cb.reset();
	while (1)
	{
		cb.print();
		char typein;
		std::cin >> typein;
		switch (typein)
		{
		case 'W':
			cb.move(Game::Direction::UP);
			break;
		case 'A':
			cb.move(Game::Direction::LEFT);
			break;
		case 'S':
			cb.move(Game::Direction::DOWN);
			break;
		case 'D':
			cb.move(Game::Direction::RIGHT);
			break;
		default:
			std::cout << "输入无效，重新输入" << "\n";
			break;
		}
	}
}