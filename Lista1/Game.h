#pragma once
#include "Colors.h"
#include "Player.h"
#include "Pawn.h"

class Game
{
public:
	Game(void);
	~Game(void);
	Colors gameColors;
	Player gamePlayer;
	Pawn gamePawn;
};

