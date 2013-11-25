#pragma once

// Constructing vectors
#include <iostream>
#include <vector>

#include <math.h>
// Include GLEW
#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

using namespace std;
using namespace glm;

class Figure
{
public:
	Figure(void);
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint drawmode;
	GLuint vertexsize;
	vector<mat4> translations;
	GLfloat height;
	GLfloat width;
	GLuint getVertexBuffer(void);
	GLuint getColorBuffer(void);
	GLuint getDrawMode(void);
	GLuint getVertexSize(void);
	vector<mat4>& Figure::getTranslations(void);
	virtual void Update(float deltaTime, glm::vec3 camera);
};

