#include "Colors.h"


Colors::Colors(void)
{
	srand (time(NULL));
	cout << "Wylosowano kolory" << endl;
	static float firstColor = (rand() % 100)/100.0;
	static float secondColor = (rand() % 100)/100.0;
	static float lastColor = (rand() % 100)/100.0;

	cout << firstColor << endl;
	cout << secondColor << endl;
	cout << lastColor << endl;

	for (int v = 0; v < 11*3 ; v++){
		g_color_buffer_data[3*v+0] = 1.0;
		g_color_buffer_data[3*v+1] = 0.0;
		g_color_buffer_data[3*v+2] = 0.0;
	}
}
	

Colors::~Colors(void)
{
}

GLuint Colors::randomlySelectedColors(void)
{

	GLuint colorbuffer;
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(g_color_buffer_data), g_color_buffer_data, GL_STATIC_DRAW);

	return colorbuffer;
}
