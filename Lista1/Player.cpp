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

void Player::endGame()
{
	std::cout << "KONIEC :(";
}