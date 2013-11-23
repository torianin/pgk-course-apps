#include "BodyPart.h"

BodyPart::BodyPart(void)
{
	drawmode = 6; // GL_TRIANGLE_FAN
	vertexsize = 12 * 3;

	height = 0.35;
	width = 0.10;

	move = 0.001;

	#ifndef buffer_data
	// Our vertices. Tree consecutive floats give a 3D vertex; Three consecutive vertices give a triangle.
	// A cube has 6 faces with 2 triangles each, so this makes 6*2=12 triangles, and 12*3 vertices
	GLfloat buffer_data[] = {
		-0.1f, -0.1f, -0.1f, // triangle 1 : begin
		-0.1f, -0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f, // triangle 1 : end
		0.1f, 0.1f, -0.1f, // triangle 2 : begin
		-0.1f, -0.1f, -0.1f,
		-0.1f, 0.1f, -0.1f, // triangle 2 : end
		0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, 0.1f,
		-0.1f, -0.1f, -0.1f,
		-0.1f, 0.1f, 0.1f,
		-0.1f, -0.1f, 0.1f,
		0.1f, -0.1f, 0.1f,
		0.1f, 0.1f, 0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, 0.1f, -0.1f,
		0.1f, -0.1f, -0.1f,
		0.1f, 0.1f, 0.1f,
		0.1f, -0.1f, 0.1f,
		0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, -0.1f,
		-0.1f, 0.1f, -0.1f,
		0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, -0.1f,
		-0.1f, 0.1f, 0.1f,
		0.1f, 0.1f, 0.1f,
		-0.1f, 0.1f, 0.1f,
		0.1f, -0.1f, 0.1f
	};
	#endif

	for (int i = 0; i < vertexsize * 3; ++i){
		vectors.push_back(buffer_data[i]);
	}

	glm::mat4 thorax = glm::mat4(1.0f);;
	translations.push_back(thorax);

	glm::mat4 right_arm = glm::translate(0.3f, 0.0f, 0.0f);
	glm::mat4 rotate_right_arm = glm::rotate(right_arm, 60.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	translations.push_back(rotate_right_arm);

	glm::mat4 left_arm = glm::translate(-0.3f, 0.0f, 0.0f);
	glm::mat4 rotate_left_arm = glm::rotate(left_arm, 60.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	translations.push_back(rotate_left_arm);

	glm::mat4 right_leg = glm::translate(0.13f, -0.35f, 0.0f);
	translations.push_back(right_leg);

	glm::mat4 left_leg = glm::translate(-0.13f, -0.35f, 0.0f);
	translations.push_back(left_leg);

	glm::mat4 head = glm::translate(0.0f, 0.50f, 0.0f);
	translations.push_back(head);

	for (unsigned int i = 0; i < BODYPARTS-1; i++)
	{
		translations[i] = translations[i] * glm::scale(1.0f, 2.0f, 1.0f);
	}
	//HEAD
	translations[5] = translations[5] * glm::scale(1.0f, 1.0f, 1.0f);

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
	//move += 0.005;

	////models[1] = glm::rotate(models[1], 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	////models[2] = glm::rotate(models[2], 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	////models[3] = glm::rotate(models[3], 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	////models[4] = glm::rotate(models[4], 5.0f, glm::vec3(0.0f, 0.0f, 1.0f));

	//projection = glm::perspective(
	//	45.0f, // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90° (extra wide) and 30° (quite zoomed in)
	//	4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
	//	0.1f,  // Near clipping plane. Keep as big as possible, or you'll get precision issues.
	//	100.0f // Far clipping plane. Keep as little as possible.
	//	);
	//// Camera matrix
	//view = glm::lookAt(
	//	glm::vec3(16, 9, 9), // Camera is at (4,3,3), in World Space
	//	glm::vec3(0, 0, 0), // and looks at the origin
	//	glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	//	);
	//// Model matrix : an identity matrix (model will be at the origin)
	//glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !
	//// Our ModelViewProjection : multiplication of our 3 matrices
	//for (unsigned int i = 0; i < BODYPARTS; i++)
	//{
	//	translations[i] = projection * view * models[i]; // Remember, matrix multiplication is the other way around
	//	translations[i] = translations[i] * glm::translate(0.0f, 0.0f, move);
	//}	
}