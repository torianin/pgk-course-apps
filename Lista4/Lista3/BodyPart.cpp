#include "BodyPart.h"

BodyPart::BodyPart(void)
{
	drawmode = 6; // GL_TRIANGLE_FAN
	vertexsize = 4;

	height = 0.35;
	width = 0.10;

	GLfloat buffer_data[8] = {
		-width / 2, -height / 2,
		width / 2, -height / 2,
		width / 2, height / 2,
		-width / 2, height / 2,
	};

	for (int i = 0; i < vertexsize * 2; ++i){
		vectors.push_back(buffer_data[i]);
	}
	glm::mat4 thorax = glm::scale(2.0f, 2.0f, 2.0f);
	translations.push_back(thorax);
	glm::mat4 right_arm = glm::translate(0.75f, 0.0f, 0.0f);
	translations.push_back(right_arm);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (unsigned int i = 0; i < (vectors.size()*sizeof(GLfloat)) / 2; i++){
		colors.push_back(1.0f);
		colors.push_back(0.0f);
		colors.push_back(0.0f);
	}

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}
