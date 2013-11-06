#include "Ball.h"

Ball::Ball(void)
{
	float radius = 0.2f;
	float center_x = 0.0f;
	float center_y = 0.0f;

	//center vertex for triangle fan
	vectors.push_back(center_x);
	vectors.push_back(center_y);

	//outer vertices of the circle
	int outerVertexCount = 59;

	for (int i = 0; i < outerVertexCount; ++i){
		float percent = (i / (float) (outerVertexCount-1));
		float rad = percent * 2 * 3.14159265358979323846;

		//vertex position
		float outer_x = center_x + radius * cos(rad);
		float outer_y = center_y + radius * sin(rad);

		vectors.push_back(outer_x);
		vectors.push_back(outer_y);
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (std::vector<float>::iterator it = vectors.begin(); it != vectors.end(); ++it)
		colors.push_back(0.05f);

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}

GLuint Ball::getVertexBuffer(void)
{
	return vertexbuffer;
}

GLuint Ball::getColorBuffer(void)
{
	return colorbuffer;
}