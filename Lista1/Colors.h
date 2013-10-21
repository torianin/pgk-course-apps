#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>

// Include GLEW
#include <GL/glew.h>

#include "Options.hpp"

using namespace std;
class Colors
{
public:
	Colors(void);
	~Colors(void);
	void generatedColors(void);
	void makeRandomColors(void);
	GLuint* getRandomedColors(void);
	GLuint* getGenratedColors(void);
private:
	GLuint randomColors[4];
	GLfloat colors[COLORS][75];
	GLuint colorbuffer[COLORS];
};

