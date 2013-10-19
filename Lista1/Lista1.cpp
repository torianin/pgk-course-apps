// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <GL/glfw.h>

#include <common/shader.hpp>

#include "Game.h"
#include "Options.hpp"

int main( void )
{
	// Initialise GLFW
	if( !glfwInit() )
	{
		fprintf( stderr, "Failed to initialize GLFW\n" );
		return -1;
	}

	glfwOpenWindowHint(GLFW_FSAA_SAMPLES, 4);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MAJOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_VERSION_MINOR, 3);
	glfwOpenWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	if( !glfwOpenWindow( 1024, 768, 0,0,0,0, 32,0, GLFW_WINDOW ) )
	{
		fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
		glfwTerminate();
		return -1;
	}

	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
	if (glewInit() != GLEW_OK) {
		fprintf(stderr, "Failed to initialize GLEW\n");
		return -1;
	}

	glfwSetWindowTitle( "Mastermind" );
	
	Game game;

	// Ensure we can capture the escape key being pressed below
	glfwEnable( GLFW_STICKY_KEYS );

	// Dark blue background
	glClearColor(0.0f, 0.0f, 0.4f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	do{

		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );

		// Use our shader
		glUseProgram(programID);
		for(int f = 0; f < FIGURES ; f++){
			// 1rst attribute buffer : vertices
			glEnableVertexAttribArray(0);
			glBindBuffer(GL_ARRAY_BUFFER, game.gamePawn.positionOfPawns()[f]);
			glVertexAttribPointer(
				0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
				3,                  // size
				GL_FLOAT,           // type
				GL_FALSE,           // normalized?
				0,                  // stride
				(void*)0            // array buffer offset
			);
		
			// 2nd attribute buffer : colors
			glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, game.gameColors.generatedColors()[game.gamePlayer.colors[f]]);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);


			glDrawArrays(GL_TRIANGLE_FAN, 0, 11); // 3 indices starting at 0 -> 1 triangle
		}
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers();

		// Strafe right
		if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_RELEASE){
				if (game.gamePlayer.choosed_pawn < game.gamePlayer.min_value + 3 ){
					game.gamePlayer.choosed_pawn += 1;
				}
			}
		}
		// Strafe left
		else if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_RELEASE){
				if (game.gamePlayer.choosed_pawn > game.gamePlayer.min_value + 0){
					game.gamePlayer.choosed_pawn -= 1;
				}
			}
		}

		else if (glfwGetKey( GLFW_KEY_1 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_1 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 0;
				std::cout << game.gamePlayer.min_value + game.gamePlayer.choosed_pawn << endl;
			}
		}

		else if (glfwGetKey( GLFW_KEY_2 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_2 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 1;
				std::cout << game.gamePlayer.min_value + game.gamePlayer.choosed_pawn << endl;
			}
		}

		else if (glfwGetKey( GLFW_KEY_3 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_3 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 2;
			}
		}

		else if (glfwGetKey( GLFW_KEY_4 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_4 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 3;
			}		
		}

		else if (glfwGetKey( GLFW_KEY_5 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_5 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 4;
			}	
		}

		else if (glfwGetKey( GLFW_KEY_6 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_6 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 5;
			}	
		}

		else if (glfwGetKey( GLFW_KEY_ENTER ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_ENTER ) == GLFW_RELEASE){
				game.gamePlayer.min_value += 4;
				game.gamePlayer.choosed_pawn = 0;
			}
		}
	} // Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	// Cleanup VBO
	//glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	return 0;
}

