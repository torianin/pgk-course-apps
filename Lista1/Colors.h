#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <cstdlib>
#include <time.h>

// Include GLEW
#include <GL/glew.h>

using namespace std;
class Colors
{
public:
	Colors(void);
	~Colors(void);
	GLuint randomlySelectedColors(void);
	
private:
	vector<string> colors;
	GLfloat g_color_buffer_data[11*3];
};

