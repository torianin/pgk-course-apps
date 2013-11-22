#pragma once

#include "Figure.h"

class Platform : public Figure
{
public:
	Platform(void);
	GLfloat dx;
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

