#pragma once

// Constructing vectors
#include <iostream>
#include <vector>

#include <math.h>
// Include GLEW
#include <GL/glew.h>

class Figure
{
public:
	Figure(void);
	GLuint vertexbuffer;
	GLuint colorbuffer;
	GLuint drawmode;
	GLuint vertexsize;
	GLfloat changevector[4];

	GLuint getVertexBuffer(void);
	GLuint getColorBuffer(void);
	GLuint getDrawMode(void);
	GLuint getVertexSize(void);
	virtual GLfloat* Update(float deltaTime);
};

