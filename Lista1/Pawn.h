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
};

