#pragma once

#include "Figure.h"
#include "Platform.h"
#include <math.h>

class Ball : public Figure
{
public:
	Ball(void);
	virtual GLfloat* Update(float deltaTime);
	int Collision(float deltaTime, Figure rect);
	void ChangeMoveX();
	void ChangeMoveY();
	GLfloat	circleDistance_x;
	GLfloat circleDistance_y;
	GLfloat differenceDistance;
	GLfloat dx;
	GLfloat dy;
private:
	GLfloat radius;
	GLfloat cornerDistance_sq;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

