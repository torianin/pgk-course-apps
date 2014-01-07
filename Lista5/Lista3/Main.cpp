// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

#include <common/shader.hpp>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

// Constructing vectors
#include <iostream>
#include <vector>

#include "Config.h"

using namespace std;
using namespace glm;

int main(void)
{
	if (!glfwInit())
	{
		fprintf(stderr, "Failed to initialize GLFW\n");
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if (!glfwOpenWindow(1024, 768, 0, 0, 0, 0, 32, 0, GLFW_WINDOW))
	{
		fprintf(stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n");
		glfwTerminate();
		return -1;
	}

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle("Teren");

	glfwEnable(GLFW_STICKY_KEYS);
	glfwSetMousePos(1024 / 2, 768 / 2);

	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders("SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader");

	// Get a handle for our "MVP" uniform
	GLuint MatrixID = glGetUniformLocation(programID, "MVP");

	// Get a handle for our "LightPosition" uniform
	glUseProgram(programID);
	
	// Kamera
	glm::mat4 ViewMatrix;
	glm::mat4 ProjectionMatrix;
	// Initial position : on +Z
	glm::vec3 position = glm::vec3(60, -60, 100);
	// Initial horizontal angle : toward -Z
	float horizontalAngle = 3.14f;
	// Initial vertical angle : none
	float verticalAngle = 0.0f;
	// Initial Field of View
	float initialFoV = 65.0f;

	float speed = 3.0f; // 3 units / second
	float mouseSpeed = 0.005f;

	// For speed computation
	double lastTime = glfwGetTime();
	int nbFrames = 0;

	Fragment first("n50e015.hgt");

	do{

		// Compute time difference between current and last frame
		double currentTime = glfwGetTime();
		float deltaTime = float(currentTime - lastTime);

		nbFrames++;
		if (currentTime - lastTime >= 1.0){ // If last prinf() was more than 1sec ago
			// printf and reset
			printf("FPS: %f Trojkatow: %d\n", 1000.0 / double(nbFrames), first.getCounter());
			nbFrames = 0;
			lastTime += 1.0;
		}

		// Clear the screen
		glClear(GL_COLOR_BUFFER_BIT);

		// Use our shader
		glUseProgram(programID);

		// Direction : Spherical coordinates to Cartesian coordinates conversion
		glm::vec3 direction(
			cos(verticalAngle) * sin(horizontalAngle),
			sin(verticalAngle),
			cos(verticalAngle) * cos(horizontalAngle)
			);

		// Right vector
		glm::vec3 right = glm::vec3(
			sin(horizontalAngle - 3.14f / 2.0f),
			0,
			cos(horizontalAngle - 3.14f / 2.0f)
			);

		// Up vector
		glm::vec3 up = glm::cross(right, direction);

		// Move forward
		if (glfwGetKey(GLFW_KEY_UP) == GLFW_PRESS){
			position += up * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(GLFW_KEY_DOWN) == GLFW_PRESS){
			position -= up * deltaTime * speed;
		}
		// Move forward
		if (glfwGetKey(GLFW_KEY_KP_ADD) == GLFW_PRESS){
			position += direction * deltaTime * speed;
		}
		// Move backward
		if (glfwGetKey(GLFW_KEY_KP_SUBTRACT) == GLFW_PRESS){
			position -= direction * deltaTime * speed;
		}
		// Strafe right
		if (glfwGetKey(GLFW_KEY_RIGHT) == GLFW_PRESS){
			position += right * deltaTime * speed;
		}
		// Strafe left
		if (glfwGetKey(GLFW_KEY_LEFT) == GLFW_PRESS){
			position -= right * deltaTime * speed;
		}
		// LOD
		if (glfwGetKey(GLFW_KEY_1) == GLFW_PRESS){
			first.generateElementBuffer(1);
		} else if (glfwGetKey(GLFW_KEY_2) == GLFW_PRESS){
			first.generateElementBuffer(2);
		} else if (glfwGetKey(GLFW_KEY_3) == GLFW_PRESS){
			first.generateElementBuffer(3);
		} else if (glfwGetKey(GLFW_KEY_4) == GLFW_PRESS){
			first.generateElementBuffer(4);
		} else if (glfwGetKey(GLFW_KEY_5) == GLFW_PRESS){
			first.generateElementBuffer(5);
		} else if (glfwGetKey(GLFW_KEY_6) == GLFW_PRESS){
			first.generateElementBuffer(6);
		} else if (glfwGetKey(GLFW_KEY_7) == GLFW_PRESS){
			first.generateElementBuffer(7);
		} else if (glfwGetKey(GLFW_KEY_8) == GLFW_PRESS){
			first.generateElementBuffer(8);
		} else if (glfwGetKey(GLFW_KEY_9) == GLFW_PRESS){
			first.generateElementBuffer(9);
		}

		float FoV = initialFoV - 5 * glfwGetMouseWheel();

		// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
		ProjectionMatrix = glm::perspective(FoV, 4.0f / 3.0f, 0.1f, 100.0f);
		// Camera matrix
		ViewMatrix = glm::lookAt(
			position,           // Camera is here
			position + direction, // and looks here : at the same position, plus "direction"
			up                  // Head is up (set to 0,-1,0 to look upside-down)
			);

		glm::mat4 ModelMatrix = glm::mat4(1.0);
		glm::mat4 MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;

		// Send our transformation to the currently bound shader, 
		// in the "MVP" uniform
		glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, first.getVertexbuffer());
		glVertexAttribPointer(
			0,                  // attribute
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
			);

		// Index buffer
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, first.getElementbuffer());

		// Draw the triangles !
		glDrawElements(
			GL_TRIANGLES,      // mode
			first.getElementbuffersize(),    // count
			GL_UNSIGNED_INT,   // type
			(void*)0           // element array buffer offset
			);

		glDisableVertexAttribArray(0);

		lastTime = currentTime;
		// Swap buffers
		glfwSwapBuffers();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(GLFW_KEY_ESC) != GLFW_PRESS &&
	glfwGetWindowParam(GLFW_OPENED));

	//glDeleteBuffers(1, &vertexbuffer);
	//glDeleteBuffers(1, &elementbuffer);
	// Cleanup VBO and shader
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);



	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}