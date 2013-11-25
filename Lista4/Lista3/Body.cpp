#include "Body.h"

Body::Body(float spawn_x, float spawn_y, float spawn_z, float rotate)
{
	drawmode = 4; // GL_TRIANGLE_FAN
	vertexsize = 12 * 3;

	height = 0.35;
	width = 0.10;

	move = 0.001;
	rotate_counter = 0.001;

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

	// 0 - prawa r�ka g�ra
	glm::mat4 right_shoulder = glm::translate(0.1f + spawn_x, 0.0f, 0.0f + spawn_z);
	translations.push_back(right_shoulder);
	// 1 - lewa r�ka g�ra
	glm::mat4 left_shoulder = glm::translate(-0.1f + spawn_x, 0.0f, 0.0f + spawn_z);
	translations.push_back(left_shoulder);
	// 2 - prawa r�ka d�
	glm::mat4 right_arm = glm::translate(0.4f + spawn_x, -0.2f, 0.0f + spawn_z);
	translations.push_back(right_arm);
	// 3 - lewa r�ka d�
	glm::mat4 left_arm = glm::translate(-0.4f + spawn_x, -0.2f, 0.0f + spawn_z);
	translations.push_back(left_arm);
	// 4
	glm::mat4 right_leg = glm::translate(0.13f + spawn_x, -0.35f, 0.0f + spawn_z);
	translations.push_back(right_leg);

	glm::mat4 down_right_leg = glm::translate(0.13f + spawn_x, -0.60f, 0.0f + spawn_z);
	translations.push_back(down_right_leg);

	glm::mat4 left_leg = glm::translate(-0.13f + spawn_x, -0.35f, 0.0f + spawn_z);
	translations.push_back(left_leg);

	glm::mat4 down_left_leg = glm::translate(-0.13f + spawn_x, -0.60f, 0.0f + spawn_z);
	translations.push_back(down_left_leg);
	
	// 8 - t��w
	glm::mat4 thorax = glm::translate(0.0f + spawn_x, 0.0f, 0.0f + spawn_z);
	translations.push_back(thorax);

	// 9 - g�owa
	head_coordinates[0] = 0.0f + spawn_x;
	head_coordinates[1] = 0.40f + spawn_y;
	head_coordinates[2] = 0.0f + spawn_z;
	glm::mat4 head = glm::translate(head_coordinates[0], head_coordinates[1], head_coordinates[2]);
	translations.push_back(head);

	models = translations;

	for (unsigned int i = 0; i < BODYPARTS; i++)
	{
		models[i] = glm::rotate(rotate, glm::vec3(0.0f, 1.0f, 0.0f)) * models[i];
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (unsigned int i = 0; i < (vectors.size()*sizeof(GLfloat))*2; i++){
		colors.push_back(1.0f);
		colors.push_back(0.0f);
		colors.push_back(0.0f);
	}

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}

void Body::Update(float deltaTime, glm::vec3 camera)
{
	move += 0.005;
	rotate_counter += 0.05;
	head_coordinates[2] += move;

	// update prawa r�ka g�ra
	translations[0] = models[0] * glm::translate(0.0f, 0.25f, move);
	translations[0] = translations[0] * glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	translations[0] = translations[0] * glm::rotate(sin(rotate_counter) * 45, glm::vec3(1.0f, 0.0f, 0.0f));
	translations[0] = translations[0] * glm::translate(0.0f, -0.25f, 0.0f);

	// update lewa r�ka g�ra
	translations[1] = models[1] * glm::translate(0.0f, 0.25f, move);
	translations[1] = translations[1] * glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	translations[1] = translations[1] * glm::rotate(-sin(rotate_counter) * 45, glm::vec3(1.0f, 0.0f, 0.0f));
	translations[1] = translations[1] * glm::translate(0.0f, -0.25f, 0.0f);

	// update prawa r�ka d�
	translations[2] = models[2] * glm::translate(0.3f, 0.05f, move);
	translations[2] = translations[2] * glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, 1.0f));
	translations[2] = translations[2] * glm::rotate(sin(rotate_counter) * 45, glm::vec3(1.0f, 0.0f, 0.0f));
	translations[2] = translations[2] * glm::translate(-0.3f, -0.05f, 0.0f);

	// lewa r�ka d�
	translations[3] = models[3] * glm::translate(-0.3f, 0.05f, move);
	translations[3] = translations[3] * glm::rotate(45.0f, glm::vec3(0.0f, 0.0f, -1.0f));
	translations[3] = translations[3] * glm::rotate(-sin(rotate_counter) * 45, glm::vec3(1.0f, 0.0f, 0.0f));
	translations[3] = translations[3] * glm::translate(0.3f, -0.05f, 0.0f);

	for (unsigned int i = 4; i < BODYPARTS; i++)
	{
		translations[i] = models[i] * glm::translate(0.0f, 0.0f, move);
	}

	for (unsigned int i = 0; i < BODYPARTS-1; i++)
	{
		translations[i] = translations[i] * glm::scale(0.5f, 2.0f, 0.5f);
	}
	//HEAD
	translations[9] = translations[9] * glm::scale(0.5f, 0.5f, 0.5f);

	projection = glm::perspective(
		60.0f, // The horizontal Field of View, in degrees : the amount of "zoom". Think "camera lens". Usually between 90� (extra wide) and 30� (quite zoomed in)
		4.0f / 3.0f, // Aspect Ratio. Depends on the size of your window. Notice that 4/3 == 800/600 == 1280/960, sounds familiar ?
		0.1f,  // Near clipping plane. Keep as big as possible, or you'll get precision issues.
		100.0f // Far clipping plane. Keep as little as possible.
	);

	// Camera matrix
	view = glm::lookAt(
		//glm::vec3(2, 3, 5), // Camera is at (4,3,3), in World Space
		camera, // Head co
		glm::vec3(0, 0, 0), // and looks at the origin
		glm::vec3(0, 1, 0)  // Head is up (set to 0,-1,0 to look upside-down)
	);

	// Model matrix : an identity matrix (model will be at the origin)
	glm::mat4 Model = glm::mat4(1.0f);  // Changes for each model !

	// Our ModelViewProjection : multiplication of our 3 matrices
	for (unsigned int i = 0; i < BODYPARTS; i++)
	{
		translations[i] = projection * view * translations[i]; // Remember, matrix multiplication is the other way around
	}	
}

GLfloat* Body::GetCameraOverHead(){
	return head_coordinates;
}