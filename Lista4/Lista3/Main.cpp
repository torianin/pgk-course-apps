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

	glfwSetWindowTitle( "Tutorial 02" );

	glfwEnable( GLFW_STICKY_KEYS );

	glEnable(GL_PROGRAM_POINT_SIZE_EXT);
    glPointSize(40);
	glLineWidth(40.0f);
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
		
	GLint MatrixID = glGetUniformLocation(programID, "Move");
	
	double lastTime = 0;
	double currentTime;
	float deltaTime;

	std::vector<Figure*> figures;
	BodyPart thorax;
	figures.push_back(&thorax);

	do{
		currentTime  = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		glClear( GL_COLOR_BUFFER_BIT );

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
			(*figure)->Update(deltaTime);
		}

		glfwSwapBuffers();

		if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){

		}

		else if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){

		}
		
		lastTime = currentTime;
		while (glfwGetTime() - lastTime < 1.0f / 60.0f);

	}
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	glfwTerminate();

	//for (std::vector<Figure*>::iterator figure = figures.begin(); figure != figures.end(); ++figure){
	//	glDeleteBuffers(1, &((*figure)->getVertexBuffer()));
	//	glDeleteBuffers(1, &((*figure)->getColorBuffer()));
	//}
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	glfwTerminate();

	return 0;
}