#pragma once

#include "Figure.h"
#include "Platform.h"
#include <math.h>

class BodyPart : public virtual Figure
{
public:
	BodyPart(void);
	void Update(float deltaTime) override;
private:
	GLfloat move;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
	vector<mat4> models;

};

