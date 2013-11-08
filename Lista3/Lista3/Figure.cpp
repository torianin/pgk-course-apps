#include "Figure.h"


Figure::Figure(void)
{
}


GLuint Figure::getVertexBuffer(void)
{
	return vertexbuffer;
}

GLuint Figure::getColorBuffer(void)
{
	return colorbuffer;
}
