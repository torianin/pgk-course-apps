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

	if( !glfwOpenWindow( 600, 600, 0,0,0,0, 32,0, GLFW_WINDOW ) )
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
		
	GLint vectorID = glGetUniformLocation(programID, "Move");
	
	double lastTime = 0;
	double currentTime;
	float deltaTime;

	std::vector<Figure*> figures;
	Background background;
	figures.push_back(&background);
	Ball ball;
	figures.push_back(&ball);
	Platform platform;
	figures.push_back(&platform);
	Blocks blocks;
	figures.push_back(&blocks);

	
	std::vector<Figure> block_figures;
	for( int i = 0; i< 5 ; i++){
		for (int j = -2; j < 3; j++){
			Block block((j*(0.3)),(i*(0.2)));
			block_figures.push_back(block);
		}
	}

	do{
		currentTime  = glfwGetTime();
		deltaTime = float(currentTime - lastTime);

		glClear( GL_COLOR_BUFFER_BIT );

		glUseProgram(programID);
		
		for (std::vector<Figure*>::iterator figure = figures.begin(); figure != figures.end(); ++figure){
			
			glProgramUniform4fv(programID, vectorID, 1, (*figure)->Update(deltaTime));
			
			if(ball.Collision(deltaTime, platform) == 1) {
				ball.dx+=ball.differenceDistance;
				ball.ChangeMoveY();
				ball.Update(deltaTime);
			} else if(ball.Collision(deltaTime, platform) > 1){
				ball.dx+=ball.differenceDistance;
				ball.ChangeMoveY();
				ball.ChangeMoveX();
				ball.Update(deltaTime);
			}

			unsigned int removeID = 0;
			for (std::vector<Figure>::iterator block = block_figures.begin(); block != block_figures.end();){
				if(ball.Collision(deltaTime, *block) == 1) {
					ball.ChangeMoveY();
					ball.Update(deltaTime);
					block = block_figures.erase(block);
					blocks.UpdateBuffer(removeID);
				} else if(ball.Collision(deltaTime, *block) == 2){
					ball.ChangeMoveX();
					ball.Update(deltaTime);
					block = block_figures.erase(block);
					blocks.UpdateBuffer(removeID);
				} else {
					++block;
				}
				removeID++;
			}

			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, (*figure)->getVertexBuffer() );
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				2,                  // size
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

			glDrawArrays((*figure)->getDrawMode(), 0, (*figure)->getVertexSize());

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);
		}

		glfwSwapBuffers();

		if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
			if(platform.dx < 0.75){
				platform.dx+= 0.5 * deltaTime * SPEED;
			}
		}

		else if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
			if(platform.dx > -0.75){
				platform.dx-= 0.5 * deltaTime * SPEED;
			}
		}
		
		lastTime = currentTime;

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