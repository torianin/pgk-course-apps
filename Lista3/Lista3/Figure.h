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
	GLfloat changevector[4];
	GLuint getVertexBuffer(void);
	GLuint getColorBuffer(void);
	virtual GLfloat* Update();
};

