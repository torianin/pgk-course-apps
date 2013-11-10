#pragma once

#include "Figure.h"

class Ball : public Figure
{
public:
	Ball(void);
	virtual GLfloat* Update();
private:
	GLfloat dx;
	GLfloat dy;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

