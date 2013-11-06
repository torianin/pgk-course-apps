#pragma once

// constructing vectors
#include <iostream>
#include <vector>

#include <math.h>

// Include GLEW
#include <GL/glew.h>

class Ball
{
public:
	Ball(void);
	GLuint getVertexBuffer(void);
	GLuint getColorBuffer(void);
private:
	GLuint vertexbuffer;
	GLuint colorbuffer;
	std::vector<GLfloat> vectors;
	std::vector<GLfloat> colors;

};

