#include "Player.h"


Player::Player(void)
{
	move = 0;
	for( int f = 0; f<FIGURES; f++)
	{
		colors[f] = 6;
	}
	choosed_pawn = 0;
	min_value = 0;
}



Player::~Player(void)
{
}

