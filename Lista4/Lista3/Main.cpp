// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

#include <common/shader.hpp>

#include "Config.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

int main( void )
{
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	if( !glfwOpenWindow( 800, 600, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Symulacja t³umu" );

	glfwEnable( GLFW_STICKY_KEYS );

	glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(40);
	glLineWidth(1.0f);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	// Enable depth test
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
		
	GLint MatrixID = glGetUniformLocation(programID, "Move");
	
	double lastTime = 0;
	double currentTime;
	float deltaTime;
	int view_mode = FULL_VIEW;
	glm::vec3 camera = glm::vec3(2, 3, 5);
	glm::vec3 lookat = glm::vec3(0, 0, 0);
	/* initialize random seed: */
	srand(time(NULL));

	std::vector<Figure*> figures;
	Body Natalia(0.0f, 0.0f, 0.0f, 0.0f, 0.3f);
	figures.push_back(&Natalia);

	Body Robcio(0.0f, 0.0f, 2.0f, 0.0f, 0.5f);
	figures.push_back(&Robcio);

	Body Maciek(-3.0f, 0.0f, -5.0f, 35.0f, 0.5f);
	figures.push_back(&Maciek);

	Body Szymon(-4.0f, 0.0f, -3.0f, 240.0f, 1.75f);
	figures.push_back(&Szymon);
	do{
		currentTime  = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		glUseProgram(programID);
		
		for (std::vector<Figure*>::iterator figure = figures.begin(); figure != figures.end(); ++figure){
			
			for (unsigned int i = 0; i < BODYPARTS; i++){
				glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &((*figure)->getTranslations()[i])[0][0]);

				glEnableVertexAttribArray(0);
				glBindBuffer(GL_ARRAY_BUFFER, (*figure)->getVertexBuffer() ); 
				glVertexAttribPointer(
					0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
					3,                  // size
					GL_FLOAT,           // type
					GL_FALSE,           // normalized?
					0,                  // stride
					(void*)0            // array buffer offset
				);

				glEnableVertexAttribArray(1);
				glBindBuffer(GL_ARRAY_BUFFER, (*figure)->getColorBuffer() );
				glVertexAttribPointer(
					1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
					3,                                // size
					GL_FLOAT,                         // type
					GL_FALSE,                         // normalized?
					0,                                // stride
					(void*)0                          // array buffer offset
				);

				glDrawArrays((*figure)->getDrawMode(), 0, (*figure)->getVertexSize() );

				glDisableVertexAttribArray(0);
				glDisableVertexAttribArray(1);
			}

			(*figure)->Update(deltaTime, camera, lookat);
		}

		glfwSwapBuffers();

		if (glfwGetKey('V') == GLFW_PRESS){
			if (glfwGetKey('V') == GLFW_RELEASE){
				if (view_mode == FULL_VIEW){
					view_mode = HEAD_VIEW;
				} else if(view_mode == HEAD_VIEW){
					view_mode = OVER_CHAR_VIEW;
				} else if(view_mode == OVER_CHAR_VIEW){
					view_mode = FULL_VIEW;
				}
			}
		}
		switch (view_mode)
		{
			case FULL_VIEW:
				camera = glm::vec3(2, 3, 5);
				lookat = glm::vec3(0, 0, 0);
				break;
			case HEAD_VIEW:
				camera = glm::vec3(Natalia.GetCameraOverHead()[0], Natalia.GetCameraOverHead()[1], Natalia.GetCameraOverHead()[2]);
				lookat = glm::vec3(Natalia.GetCameraLookAt()[0], Natalia.GetCameraLookAt()[1], Natalia.GetCameraLookAt()[2]);
				break;
			case OVER_CHAR_VIEW:
				camera = glm::vec3(Natalia.GetCameraMoreOverHead()[0], Natalia.GetCameraMoreOverHead()[1] + 2.0, Natalia.GetCameraMoreOverHead()[2] + 2.0);
				lookat = glm::vec3(Natalia.GetCameraLookAt()[0], Natalia.GetCameraLookAt()[1], Natalia.GetCameraLookAt()[2]);
				break;
			default:
				camera = glm::vec3(2, 3, 5);
				break;
		}
		lastTime = currentTime;
		while (glfwGetTime() - lastTime < 1.0f / 60.0f);

	}
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	glfwTerminate();

	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}