#pragma once
// Include standard headers
#include <iostream>

// Include GLEW
#include <GL/glew.h>

class Pawn
{
public:
	Pawn(void);
	~Pawn(void);
	GLuint* positionOfPawns(void);
};

