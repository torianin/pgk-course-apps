#pragma once

#include "Figure.h"

class Platform : public Figure
{
public:
	Platform(void);
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

