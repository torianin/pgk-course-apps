#include "Colors.h"


Colors::Colors(void)
{

}
	

Colors::~Colors(void)
{
}

GLuint* Colors::generatedColors(void)
{
	static GLfloat colors[7][33];
	
	for (int o = 0; o < 7 ; o ++){
		for (int v = 0; v < 33 ; v++){
			if (o == 0){
				colors[o][3*v+0] = 1.0;
				colors[o][3*v+1] = 0.0;
				colors[o][3*v+2] = 0.0;
			} else if ( o == 1) {
				colors[o][3*v+0] = 0.0;
				colors[o][3*v+1] = 1.0;
				colors[o][3*v+2] = 0.0;
			} else if ( o == 2) {
				colors[o][3*v+0] = 1.0;
				colors[o][3*v+1] = 1.0;
				colors[o][3*v+2] = 1.0;
			} else if ( o == 3) {
				colors[o][3*v+0] = 0.0;
				colors[o][3*v+1] = 0.0;
				colors[o][3*v+2] = 1.0;
			} else if ( o == 4) {
				colors[o][3*v+0] = 1.0;
				colors[o][3*v+1] = 1.0;
				colors[o][3*v+2] = 0.0;
			} else if ( o == 5) {
				colors[o][3*v+0] = 0.0;
				colors[o][3*v+1] = 1.0;
				colors[o][3*v+2] = 1.0;
			} else if ( o == 6) {
				colors[o][3*v+0] = 0.0;
				colors[o][3*v+1] = 0.0;
				colors[o][3*v+2] = 0.0;
			}
		}
	}


	GLuint colorbuffer[7];
	glGenBuffers(7, colorbuffer);

	for (int o = 0; o < 7 ; o ++){
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[o]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors[o]), colors[o], GL_STATIC_DRAW);
	}

	return colorbuffer;
}