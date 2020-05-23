#include "tile.h"

bool Game::operator==(const tile& tile1, const tile& tile2)
{
	if (tile1.getvalue() == tile2.getvalue())
	{
		if (tile1.getflag() == false && tile2.getflag() == false)
		{
			return true;
		}
	}
	return false;
}
