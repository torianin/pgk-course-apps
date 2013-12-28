#pragma once

#include "Figure.h"

class Blocks : public Figure
{
public:
	Blocks(void);
	GLfloat* Update(float deltaTime);
	void UpdateBuffer(int removeID);
private:
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
};

