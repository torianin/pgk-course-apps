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

GLuint Figure::getDrawMode(void)
{
	return drawmode;
}

GLuint Figure::getVertexSize(void)
{
	return vertexsize;
}

GLfloat* Figure::Update(float deltaTime)
{
	changevector[0]=0.0;
	changevector[1]=0.0;
	changevector[2]=0.0;
	changevector[3]=0.0;

	return changevector;
}