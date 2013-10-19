#include "Pawn.h"


Pawn::Pawn(void)
{

}


Pawn::~Pawn(void)
{
}

GLuint* Pawn::positionOfPawns(void)
{
	static GLfloat g_vertex_buffer_data_template[] = { 
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
		0.075f, -0.075f, 0.0f,
	};
	static GLfloat firstObiect[11*3];

	for (int v = 0; v < 11 ; v++){
		firstObiect[3*v+0] = g_vertex_buffer_data_template[3*v+0];
		firstObiect[3*v+1] = g_vertex_buffer_data_template[3*v+1];
		firstObiect[3*v+2] = g_vertex_buffer_data_template[3*v+2];
	}
	
	static GLfloat secondObiect[11*3];

	for (int v = 0; v < 11 ; v++){
		secondObiect[3*v+0] = g_vertex_buffer_data_template[3*v+0]+0.25;
		secondObiect[3*v+1] = g_vertex_buffer_data_template[3*v+1];
		secondObiect[3*v+2] = g_vertex_buffer_data_template[3*v+2];
	}

	GLuint vertexbuffer[2];
	glGenBuffers(2, vertexbuffer);

	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstObiect), firstObiect, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondObiect), secondObiect, GL_STATIC_DRAW);
	
	return vertexbuffer;
}