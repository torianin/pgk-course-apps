#pragma once
// Include standard headers
#include <iostream>

// Include GLEW
#include <GL/glew.h>
#include "Options.hpp"

class Pawn
{
public:
	Pawn(void);
	~Pawn(void);
	GLuint* positionOfPawns(void);
	GLfloat g_vertex_buffer_data_template[33];
	GLuint vertexbuffer[FIGURES];
	GLfloat objects[FIGURES][11*3];
};

