#include "Pawn.h"

Pawn::Pawn(void)
{
	 GLfloat g_vertex_buffer_data_template_constructor[33] = {
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
	 for(int i = 0; i< 33; i++)
	 {
		 g_vertex_buffer_data_template[i] = g_vertex_buffer_data_template_constructor[i];
	 }
}


Pawn::~Pawn(void)
{
}

void Pawn::positionOfPawns(void)
{
	//Du¿e pionki
	for(int r = 0; r < ROWS ; r++){
		for (int c = 0; c < COLUMNS ; c++){
			for (int v = 0; v < 11 ; v++){
				objects[(4*r)+c][3*v+0] = g_vertex_buffer_data_template[3*v+0]-0.8+(0.25*c);
				objects[(4*r)+c][3*v+1] = g_vertex_buffer_data_template[3*v+1]-0.8+(0.25*r);
				objects[(4*r)+c][3*v+2] = g_vertex_buffer_data_template[3*v+2];
			}
		}
	}
	//Ma³e pinki
	for(int r = 0; r < CHECK_ROWS ; r++){
		for (int c = 0; c < CHECK_COLUMNS ; c++){
			for (int v = 0; v < 11 ; v++){
				objects[PLAYER_FIGURES+(2*r)+c][3*v+0] = (g_vertex_buffer_data_template[3*v+0]+0.3+(0.25*c))/2.1;
				objects[PLAYER_FIGURES+(2*r)+c][3*v+1] = (g_vertex_buffer_data_template[3*v+1]-1.8+(0.262*r))/2.1;
				objects[PLAYER_FIGURES+(2*r)+c][3*v+2] = g_vertex_buffer_data_template[3*v+2];
			}
		}
	}

	glGenBuffers(FIGURES, vertexbuffer);
	
	for(int f = 0; f < FIGURES ; f++){
			glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[f]);
			glBufferData(GL_ARRAY_BUFFER, sizeof(objects[f]), objects[f], GL_STATIC_DRAW);
	}
}

GLuint* Pawn::getPositionOfPawns(void)
{
	return vertexbuffer;
}