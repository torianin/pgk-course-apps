#include "Background.h"


Background::Background(void)
{
	drawmode = 3; // GL_TRIANGLE_FAN
	vertexsize = 5;
	GLfloat buffer_data[10] = {
		-0.5, -0.5,
		0.5, -0.5,
		0.5, 0.5,
		-0.5, 0.5,
		-0.5, -0.5,
	};

	for (int i = 0; i < vertexsize*2; ++i){
		std::cout << buffer_data[i] << std::endl;
		vectors.push_back(buffer_data[i]);	
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (unsigned int i=0; i < (vectors.size()*sizeof(GLfloat))/2; i++){
		colors.push_back(1.0f);
		colors.push_back(0.0f);
		colors.push_back(0.0f);
	}

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}

GLfloat* Background::Update()
{
	changevector[0]=0.0;
	changevector[1]=0.0;
	changevector[2]=0.0;
	changevector[3]=0.0;

	return changevector;
}