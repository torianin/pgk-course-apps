#pragma once

#include "Figure.h"

class Ball : public Figure
{
public:
	Ball(void);
	virtual GLfloat* Update();
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

