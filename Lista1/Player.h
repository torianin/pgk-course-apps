#pragma once
#include "Options.hpp"
#include <iostream>

// Include GLEW
#include <GL/glew.h>
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
	int player_colors[6];
	int randomed_colors[6];
	int game;
	GLuint drawPlayerChoose(void);
	void moveRight();
	void moveLeft();
	void moveUp();
	void winGame();
	void loseGame();

private:
	GLfloat board[15];
	GLfloat board_template[15];

};

