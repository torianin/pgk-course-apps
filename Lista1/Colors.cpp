#include "Colors.h"


Colors::Colors(void)
{
	srand (time(NULL));
}
	

Colors::~Colors(void)
{
}

void Colors::makeRandomColors(void)
{
	for(int i =0; i < 4; i++){
		randomColors[i] = rand() % 6;
		std::cout << randomColors[i]+1;
	}
}

GLuint* Colors::getRandomedColors(void)
{
	return randomColors;
}

void Colors::generatedColors(void)
{

	for (int o = 0; o < COLORS ; o ++){
		for (int v = 0; v < 25 ; v++){
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
				colors[o][3*v+0] = 0.3;
				colors[o][3*v+1] = 0.3;
				colors[o][3*v+2] = 0.3;
			} else if ( o == 7) {
				colors[o][3*v+0] = 0.9;
				colors[o][3*v+1] = 0.6;
				colors[o][3*v+2] = 0.3;
			}
		}
	}

	glGenBuffers(COLORS, colorbuffer);

	for (int o = 0; o < COLORS ; o ++){
		glBindBuffer(GL_ARRAY_BUFFER, colorbuffer[o]);
		glBufferData(GL_ARRAY_BUFFER, sizeof(colors[o]), colors[o], GL_STATIC_DRAW);
	}
}

GLuint* Colors::getGenratedColors(void)
{
	return colorbuffer;
}