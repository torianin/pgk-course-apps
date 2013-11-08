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
	GLuint getVertexBuffer(void);
	GLuint getColorBuffer(void);

};

