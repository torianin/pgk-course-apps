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

GLfloat* Figure::Update()
{
	changevector[0]=0.0;
	changevector[1]=0.0;
	changevector[2]=0.0;
	changevector[3]=0.0;

	return changevector;
}