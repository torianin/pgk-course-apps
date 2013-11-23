#pragma once

#include "Figure.h"
#include "Platform.h"
#include <math.h>
#include "Config.h"

class BodyPart : public virtual Figure
{
public:
	BodyPart(void);
	void Update(float deltaTime) override;
private:
	GLfloat move;
	glm::mat4 projection;
	glm::mat4 view;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
	vector<mat4> models;

};

