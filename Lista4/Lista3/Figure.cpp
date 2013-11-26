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

vector<mat4>& Figure::getTranslations(void)
{
	return translations;
}

void Figure::Update(float deltaTime, glm::vec3 camera, glm::vec3 lookat)
{

}