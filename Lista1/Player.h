#pragma once
#include "Options.hpp"

class Player
{
public:
	Player(void);
	~Player(void);
	int move;
	int colors[FIGURES];
	int choosed_pawn;
	int min_value;
};

