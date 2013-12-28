#include "Blocks.h"


Blocks::Blocks(void)
{
	drawmode = 0; // GL_TRIANGLE_FAN
	vertexsize = 50;

	for (int r = 0; r < 5; ++r){	
		for (int c = 0; c < 5; ++c){
			vectors.push_back(c*0.3);
			vectors.push_back(r*0.2);
			vectors.push_back(c*0.3+0.1);
			vectors.push_back(r*0.2);
		}
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (unsigned int i=0; i < (vectors.size()*sizeof(GLfloat))/2; i++){
		if( i < 10 ){
			colors.push_back(0.0f);
			colors.push_back(1.0f);
			colors.push_back(1.0f);
		} else if ( i < 20 ){
			colors.push_back(1.0f);
			colors.push_back(1.0f);
			colors.push_back(0.0f);
		} else if ( i < 30 ){
			colors.push_back(1.0f);
			colors.push_back(0.3f);
			colors.push_back(0.1f);
		} else if ( i < 40 ){
			colors.push_back(1.0f);
			colors.push_back(0.0f);
			colors.push_back(0.0f);
		} else if ( i < 50 ){
			colors.push_back(0.7f);
			colors.push_back(0.1f);
			colors.push_back(0.5f);
		}
	}

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);

}

GLfloat* Blocks::Update(float deltaTime)
{
	changevector[0]=-0.65;
	changevector[1]=0.0;
	changevector[2]=0.0;
	changevector[3]=0.0;

	return changevector;
}

void Blocks::UpdateBuffer(int removeID)
{
	vertexsize = vertexsize-2;
	vectors.erase(vectors.begin()+(removeID*4),vectors.begin()+(removeID*4)+4);
	glGenBuffers(1, &vertexbuffer); 
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	colors.erase(colors.begin()+(removeID*4)*3/2,colors.begin()+((removeID*4)+4)*3/2);
	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}