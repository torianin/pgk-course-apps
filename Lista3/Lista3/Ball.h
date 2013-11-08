#pragma once

#include "Figure.h"

class Ball : public Figure
{
public:
	Ball(void);
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

