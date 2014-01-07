#pragma once
// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

#include <glm/glm.hpp>

// reading an entire binary file
#include <fstream>
#include <cstdio>
#include <iostream>
#include <climits>
#include <intrin.h>

// Constructing vectors
#include <iostream>
#include <vector>

using namespace std;
using namespace glm;

class Fragment
{
public:
	Fragment();
	int counter;
	GLuint vertexbuffer;
	GLuint elementbuffer;
	GLsizei elementbuffersize;
	int getCounter();
	GLuint getVertexbuffer();
	GLuint getElementbuffer();
	GLsizei getElementbuffersize();
};

