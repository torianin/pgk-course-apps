#include "Background.h"


Background::Background(void)
{
	drawmode = 1; // GL_TRIANGLE_FAN
	vertexsize = 12*29*25+12;

	float radius = 0.05f;

	//outer vertices of the circle
	int outerVertexCount = 7;
	float center_x;
	float center_y = 0.0;
	float height = sqrt(3)/2 * 0.10;
	for (int k = 1; k < 25; ++k){
		for (int j = 0; j < 29; ++j){
			
			center_x = 0.075f*j;

			if(j % 2 == 0){
				center_y = height * k;
			} else {
				center_y = height * k + height/2;
			}

			for (int i = 0; i < outerVertexCount; ++i){
				float percent = (i / (float) (outerVertexCount-1));
				float rad = percent * 2 * 3.14159265358979323846;

				//vertex position
				float outer_x = center_x + radius * cos(rad);
				float outer_y = center_y + radius * sin(rad);

				if(i == 0 || i == 6){
					vectors.push_back(outer_x );
					vectors.push_back(outer_y );
				} else {
					vectors.push_back(outer_x );
					vectors.push_back(outer_y );
					vectors.push_back(outer_x );
					vectors.push_back(outer_y );
				}
			}
		}
	}

	GLfloat border_template[] = {
		0.1,0.0,
		0.1,2.05,
		0.1,2.05,
		1.9,2.05,
		1.9,2.05,
		1.9,0.0
	};
	for (int i = 0; i < 12; i++)
	{
		vectors.push_back(border_template[i]);
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (unsigned int i=0; i < (12*28*25)-50; i++){
		colors.push_back(0.3f);
		colors.push_back(0.3f);
		colors.push_back(0.3f);
	}

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}

GLfloat* Background::Update(float deltaTime)
{
	changevector[0]=-1.0;
	changevector[1]=-1.1;
	changevector[2]=0.0;
	changevector[3]=0.0;

	return changevector;
}