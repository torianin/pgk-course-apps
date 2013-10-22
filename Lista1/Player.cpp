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
	game = 0;

	GLfloat board_constructor[] = { 
		-0.90f, -0.91f, 0.0f,
		-0.70f, -0.91f, 0.0f,
		-0.70f, -0.69f, 0.0f,
		-0.90f, -0.69f, 0.0f,
		-0.90f, -0.91f, 0.0f,
	};
	for(int i = 0; i < 15; i++)
	 {
		 board[i] = board_constructor[i];
	 }
	for(int i = 0; i < 15; i++)
	 {
		 board_template[i] = board_constructor[i];
	 }

	for( int f = 0; f<6; f++)
	{
		player_colors[f] = 0;
		randomed_colors[f] = 0;
	}
}



Player::~Player(void)
{
}

void Player::moveRight()
{
		for (int v = 0; v < 5 ; v++){
			board[3*v+0] = board[3*v+0]+0.25;
			board[3*v+1] = board[3*v+1];
			board[3*v+2] = board[3*v+2];
		}
}

void Player::moveLeft()
{
		for (int v = 0; v < 5 ; v++){
			board[3*v+0] = board[3*v+0]-0.25;
			board[3*v+1] = board[3*v+1];
			board[3*v+2] = board[3*v+2];
		}
}

void Player::moveUp()
{
		for (int v = 0; v < 5 ; v++){
			board[3*v+0] = board_template[3*v+0];
			board[3*v+1] = board[3*v+1]+0.252;
			board[3*v+2] = board[3*v+2];
		}
}

GLuint Player::drawPlayerChoose(void)
{
	GLuint vertexbuffer;

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(board), board, GL_STATIC_DRAW);

	return vertexbuffer;
}

void Player::loseGame()
{
	game = LOSE_GAME;
}

void Player::winGame()
{
	game = WIN_GAME;
}

GLuint* Player::drawHappySmile()
{
	GLfloat smile[] = { 
		0.0f, 0.0f, 0.0f,
		0.75f, -0.75f, 0.0f,
		1.00f, 0.0f, 0.0f,
		0.75f, 0.75f, 0.0f,
		0.0f, 1.00f, 0.0f, 
		0.0f, 1.00f, 0.0f, 
		-0.75f, 0.75f, 0.0f,
		-1.00f, 0.0f, 0.0f,
		-0.75f, -0.75f, 0.0f,
		0.0f, -1.00f, 0.0f,
		0.75f, -0.75f, 0.0f
	};
		
	GLfloat happy[] = { 
		0.0f, 0.0f, 0.0f,
		0.50f, -0.50f, 0.0f,
		0.75f, 0.0f, 0.0f,
		-0.75f, 0.0f, 0.0f,
		-0.50f, -0.50f, 0.0f,
		0.0f, -0.75f, 0.0f,
		0.50f, -0.50f, 0.0f
	};
	
	GLfloat sad[] = { 
		0.0f, -0.50f, 0.0f,
		0.50f, 0.0f, 0.0f,
		0.75f, -0.50f, 0.0f,
		-0.75f, -0.50f, 0.0f,
		-0.50f, 0.0f, 0.0f,
		0.0f, 0.25f, 0.0f,
		0.50f, 0.0f, 0.0f

	};

	GLfloat eye[] = {
		0.0f, 0.0f, 0.0f,
		0.075f, -0.075f, 0.0f,
		0.10f, 0.0f, 0.0f,
		0.075f, 0.075f, 0.0f,
		0.0f, 0.10f, 0.0f, 
		0.0f, 0.10f, 0.0f, 
		-0.075f, 0.075f, 0.0f,
		-0.10f, 0.0f, 0.0f,
		-0.075f, -0.075f, 0.0f,
		0.0f, -0.10f, 0.0f,
		0.075f, -0.075f, 0.0f
	 };

	GLfloat eye2[33];
	
	for (int v = 0; v < 11 ; v++){
		eye[3*v+0] = eye[3*v+0]+0.5;
		eye[3*v+1] = eye[3*v+1]+0.4;
		eye[3*v+2] = eye[3*v+2];
	}

	for (int v = 0; v < 11 ; v++){
		eye2[3*v+0] = eye[3*v+0]-1.0;
		eye2[3*v+1] = eye[3*v+1];
		eye2[3*v+2] = eye[3*v+2];
	}

	GLuint vertexbuffer[5];
	glGenBuffers(5, vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(smile), smile, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(sad), sad, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[2]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(eye), eye, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[3]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(eye2), eye2, GL_STATIC_DRAW);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[4]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(happy), happy, GL_STATIC_DRAW);
	return vertexbuffer;
}