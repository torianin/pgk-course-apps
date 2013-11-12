#pragma once

#include "Figure.h"
#include "Platform.h"
#include <math.h>

class Ball : public Figure
{
public:
	Ball(void);
	virtual GLfloat* Update(float deltaTime);
	bool Collision(float deltaTime, Platform rect);
	void ChangeMoveX();
	void ChangeMoveY();
private:
	GLfloat	circleDistance_x;
	GLfloat circleDistance_y;
	GLfloat radius;
	GLfloat dx;
	GLfloat dy;
	GLfloat cornerDistance_sq;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

