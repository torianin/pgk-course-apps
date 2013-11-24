#pragma once

#include "Figure.h"
#include "Platform.h"
#include <math.h>
#include "Config.h"

class Body : public virtual Figure
{
public:
	Body(float spawn_x, float spawn_y, float spawn_z, float rotate);
	void Update(float deltaTime) override;
private:
	GLfloat move;
	GLfloat rotate_counter;
	glm::mat4 projection;
	glm::mat4 view;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
	vector<mat4> models;
};

