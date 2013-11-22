#pragma once

#include "Figure.h"
#include "Platform.h"
#include <math.h>

class BodyPart : public Figure
{
public:
	BodyPart(void);
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

