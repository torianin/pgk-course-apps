#pragma once

#include "Figure.h"

class Background : public Figure
{
public:
	Background(void);
	GLfloat* Update(float deltaTime);
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

