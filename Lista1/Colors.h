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
	GLuint* generatedColors(void);
};

