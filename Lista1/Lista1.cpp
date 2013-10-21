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
	if( !glfwOpenWindow( 800, 600, 0,0,0,0, 32,0, GLFW_WINDOW ) )
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

	// Dark gray background
	glClearColor(0.30f, 0.30f, 0.30f, 0.0f);

	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	// Create and compile our GLSL program from the shaders
	GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );

	game.gameColors.makeRandomColors();
	game.gameColors.generatedColors();

	static  GLfloat board[] = { 
		-0.92f, -0.93f, 0.0f,
		 0.33f, -0.93f, 0.0f,
		 0.33f, -0.67f, 0.0f,
		-0.92f, -0.67f, 0.0f,
		-0.92f, -0.42f, 0.0f,
		 0.33f, -0.42f, 0.0f,
		 0.33f, -0.17f, 0.0f,
		-0.92f, -0.17f, 0.0f,
		-0.92f,  0.08f, 0.0f,
		 0.33f,  0.08f, 0.0f,
		 0.33f,  0.33f, 0.0f,
		-0.92f,  0.33f, 0.0f,
		-0.92f,  0.58f, 0.0f,
		 0.33f,  0.58f, 0.0f,
		 0.33f,  0.83f, 0.0f,
		-0.92f,  0.83f, 0.0f,
		-0.92f,  1.08f, 0.0f,
		 0.33f,  1.08f, 0.0f,
		 0.33f,  1.33f, 0.0f,
		-0.92f,  1.33f, 0.0f,
		-0.92f, -0.93f, 0.0f,
		 0.33f, -0.93f, 0.0f,
		 0.33f,  1.33f, 0.0f,
		 0.08f,  1.33f, 0.0f,
		 0.08f,  -0.93f, 0.0f,
	};

	GLuint vertexbuffer;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(board), board, GL_STATIC_DRAW);

	
	
	do{
		// Clear the screen
		glClear( GL_COLOR_BUFFER_BIT );
	
		// Use our shader
		glUseProgram(programID);
		
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
			glBindBuffer(GL_ARRAY_BUFFER, game.gameColors.getGenratedColors()[7]);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);
		// Draw the triangle !
		glDrawArrays(GL_LINE_STRIP, 0, 25); // 3 indices starting at 0 -> 1 triangle

		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers();
		
		// 1rst attribute buffer : vertices
		glEnableVertexAttribArray(0);
		glBindBuffer(GL_ARRAY_BUFFER, game.gamePlayer.drawPlayerChoose());
		glVertexAttribPointer(
			0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
			3,                  // size
			GL_FLOAT,           // type
			GL_FALSE,           // normalized?
			0,                  // stride
			(void*)0            // array buffer offset
		);

		glEnableVertexAttribArray(1);
		glBindBuffer(GL_ARRAY_BUFFER, game.gameColors.getGenratedColors()[7]);
		glVertexAttribPointer(
			1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
			3,                                // size
			GL_FLOAT,                         // type
			GL_FALSE,                         // normalized?
			0,                                // stride
			(void*)0                          // array buffer offset
		);
		// Draw the triangle !
		glDrawArrays(GL_LINE_STRIP, 0, 5); // 3 indices starting at 0 -> 1 triangle
		
		glDisableVertexAttribArray(0);
		glDisableVertexAttribArray(1);

		// Swap buffers
		glfwSwapBuffers();

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
			glBindBuffer(GL_ARRAY_BUFFER, game.gameColors.getGenratedColors()[game.gamePlayer.colors[f]]);
			glVertexAttribPointer(
				1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
				3,                                // size
				GL_FLOAT,                         // type
				GL_FALSE,                         // normalized?
				0,                                // stride
				(void*)0                          // array buffer offset
			);


			glDrawArrays(GL_TRIANGLE_FAN, 0, 11); // 3 indices starting at 0 -> 1 triangle

			glDisableVertexAttribArray(0);
			glDisableVertexAttribArray(1);

			// Swap buffers
			glfwSwapBuffers();
		}
		
		// Strafe right
		if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_RIGHT ) == GLFW_RELEASE){
				if (game.gamePlayer.choosed_pawn < 3 ){
					game.gamePlayer.choosed_pawn += 1;
					game.gamePlayer.moveRight();
				}
			}
		}
		// Strafe left
		else if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_LEFT ) == GLFW_RELEASE){
				if (game.gamePlayer.choosed_pawn > 0){
					game.gamePlayer.choosed_pawn -= 1;
					game.gamePlayer.moveLeft();
				}
			}
		}

		else if (glfwGetKey( GLFW_KEY_1 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_1 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 0;
			}
		}

		else if (glfwGetKey( GLFW_KEY_2 ) == GLFW_PRESS){
			if (glfwGetKey( GLFW_KEY_2 ) == GLFW_RELEASE){
				game.gamePlayer.colors[game.gamePlayer.min_value + game.gamePlayer.choosed_pawn] = 1;
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
				int very_good = 0;
				int almost_good = 0;
				//Sprawdzamy ktore kolory sa takie same jesli nie sa to zwiekszamy licznik tego koloru
				for(int i=0; i<4; i++){
					if(game.gamePlayer.colors[i+game.gamePlayer.min_value] == game.gameColors.getRandomedColors()[i]){
						very_good += 1;
					} else {
						game.gamePlayer.player_colors[game.gamePlayer.colors[i+game.gamePlayer.min_value]] +=1;
						game.gamePlayer.randomed_colors[game.gameColors.getRandomedColors()[i]] +=1;
					}
				}
				for(int i = 0; i<6; i++)
				{
					if(game.gamePlayer.player_colors[i]!=0 && game.gamePlayer.randomed_colors[i]!=0)
					{
						if(game.gamePlayer.player_colors[i] < game.gamePlayer.randomed_colors[i])
						{
							almost_good += game.gamePlayer.player_colors[i];
						} else {
							almost_good += game.gamePlayer.randomed_colors[i];
						}
					}
					game.gamePlayer.player_colors[i] = 0;
					game.gamePlayer.randomed_colors[i] = 0;
				}

				for(int i = 0; i<very_good; i++)
				{
					game.gamePlayer.colors[32+i+game.gamePlayer.min_value]=0;
				}
				for(int i = very_good; i<very_good+almost_good; i++)
				{
					game.gamePlayer.colors[32+i+game.gamePlayer.min_value]=2;
				}
				game.gamePlayer.min_value += 4;
				game.gamePlayer.choosed_pawn = 0;
				if(game.gamePlayer.move < 7){
					game.gamePlayer.moveUp();
					game.gamePlayer.move += 1;
				} else {
					game.gamePlayer.endGame();
				}
			}
		}
	} 
	// Check if the ESC key was pressed or the window was closed
	while( glfwGetKey( GLFW_KEY_ESC ) != GLFW_PRESS && glfwGetKey( GLFW_KEY_Q ) != GLFW_PRESS &&
		   glfwGetWindowParam( GLFW_OPENED ) );

	// Close OpenGL window and terminate GLFW
	glfwTerminate();

	// Cleanup VBO
	glDeleteBuffers(FIGURES, game.gamePawn.positionOfPawns());
	glDeleteBuffers(7, game.gameColors.getGenratedColors());
	glDeleteProgram(programID);
	glDeleteVertexArrays(1, &VertexArrayID);

	return 0;
}

