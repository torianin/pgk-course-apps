#pragma once

#include "Figure.h"
#include "Platform.h"
#define _USE_MATH_DEFINES
#include <math.h>
#include "Config.h"

class Body : public virtual Figure
{
public:
	Body(float spawn_x, float spawn_y, float spawn_z, float rotate, float size);
	void Update(float deltaTime, glm::vec3 camera, glm::vec3 lookat) override;
	glm::vec4 GetCameraOverHead();
	glm::vec4 GetCameraLookAt();
	glm::vec4 GetCameraMoreOverHead();
private:
	GLfloat move;
	GLfloat rotate_counter;
	GLfloat stomach_value;
	glm::vec4 zeroCamera;
	glm::vec4 transformedCamera;
	glm::vec4 moreCamera;
	glm::vec4 moreTransformedCamera;
	glm::vec4 zeroLookAt;
	glm::vec4 transformedLookAt;
	glm::mat4 projection;
	glm::mat4 view;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;
	vector<mat4> models;
	GLfloat head_coordinates[3];
};

