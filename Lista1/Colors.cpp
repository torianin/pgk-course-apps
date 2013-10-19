#include "Colors.h"


Colors::Colors(void)
{

}
	

Colors::~Colors(void)
{
}

GLuint* Colors::randomlySelectedColors(void)
{
	static GLfloat firstObiectColor[11*3];

	for (int v = 0; v < 11*3 ; v++){
		firstObiectColor[3*v+0] = 1.0;
		firstObiectColor[3*v+1] = 0.0;
		firstObiectColor[3*v+2] = 0.0;
	}
	
	static GLfloat secondObiectColor[11*3];

	for (int v = 0; v < 11*3 ; v++){
		secondObiectColor[3*v+0] = 0.0;
		secondObiectColor[3*v+1] = 1.0;
		secondObiectColor[3*v+2] = 0.0;
	}

	GLuint colorbuffer[2];

	glGenBuffers(2, colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[0]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(firstObiectColor), firstObiectColor, GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[1]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(secondObiectColor), secondObiectColor, GL_STATIC_DRAW);

	return colorbuffer;
}