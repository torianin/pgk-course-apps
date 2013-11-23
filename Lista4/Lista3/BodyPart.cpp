#include "BodyPart.h"

BodyPart::BodyPart(void)
{
	drawmode = 6; // GL_TRIANGLE_FAN
	vertexsize = 4;

	height = 0.35;
	width = 0.10;

	move = 0.1;

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

	glm::mat4 right_arm = glm::translate(width, 0.0f, 0.0f);
	glm::mat4 rotate_right_arm = glm::rotate(right_arm, 60.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	translations.push_back(rotate_right_arm);

	glm::mat4 left_arm = glm::translate(-width, 0.0f, 0.0f);
	glm::mat4 rotate_left_arm = glm::rotate(left_arm, 60.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	translations.push_back(rotate_left_arm);

	glm::mat4 right_leg = glm::translate(width, -height, 0.0f);
	translations.push_back(right_leg);

	glm::mat4 left_leg = glm::translate(-width, -height, 0.0f);
	translations.push_back(left_leg);

	models = translations;
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

void BodyPart::Update(float deltaTime)
{
	glm::mat4 Projection = glm::perspective(
		45.0f, // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,  // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f // Far clipping plane. Keep as little as possible.
		);
	// Camera matrix
	glm::mat4 View = glm::lookAt(
		glm::vec3(4, 3, 3), // Camera is at (4,3,3), in World Space
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
		);
	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	// Our ModelViewProjection : multiplication of our 3 matrices
	for (unsigned int i = 0; i < 5; i++)
	{
		translations[i] = Projection * View * models[i]; // Remember, matrix multiplication is the other way around
	}	
}