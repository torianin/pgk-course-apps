#include "Ball.h"

Ball::Ball(void)
{
	drawmode = 6; // GL_TRIANGLE_FAN
	vertexsize = 15;

	dx = 0.5;
	dy = 0.5;
	changevector[0]=0.0;
	changevector[1]=-0.5;

	radius = 0.05f;
	float center_x = 0.0f;
	float center_y = 0.0f;

	//center vertex for triangle fan
	vectors.push_back(center_x);
	vectors.push_back(center_y);

	//outer vertices of the circle
	int outerVertexCount = 14;

	for (int i = 0; i < outerVertexCount; ++i){
		float percent = (i / (float) (outerVertexCount-1));
		float rad = percent * 2 * 3.14159265358979323846;

		//vertex position
		float outer_x = center_x + radius * cos(rad);
		float outer_y = center_y + radius * sin(rad);

		vectors.push_back(outer_x);
		vectors.push_back(outer_y);
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(GLfloat), vectors.data(), GL_STATIC_DRAW);

	for (unsigned int i=0; i < (vectors.size()*sizeof(GLfloat))/2; i++){
		colors.push_back(0.0f);
		colors.push_back(0.0f);
		colors.push_back(1.0f);
	}

	glGenBuffers(1, &colorbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
	glBufferData(GL_ARRAY_BUFFER, colors.size()*sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
}

GLfloat* Ball::Update(float deltaTime)
{
	if( changevector[0]+dx*deltaTime > 0.95 || changevector[0]+dx*deltaTime < -0.95) {
		dx = -dx;
	}  else if ( changevector[1]+dy*deltaTime > 0.95){
		dy = -dy;
	} 

	changevector[0]=changevector[0] + dx * deltaTime;
	changevector[1]=changevector[1] + dy * deltaTime;
	changevector[2]=0.0;
	changevector[3]=0.0;

	return changevector;
}

void Ball::ChangeMoveX()
{
		dx = -dx;
}

void Ball::ChangeMoveY()
{
		dy = -dy;
}

int Ball::Collision(float deltaTime, Figure rect)
{
	circleDistance_x = abs(changevector[0] - rect.changevector[0]);
    circleDistance_y = abs(changevector[1] - rect.changevector[1]);
    if (circleDistance_x > (rect.width/2 + radius)) { return 0; }
    if (circleDistance_y > (rect.height/2 + radius)) { return 0; }

    if (circleDistance_x <= (rect.width/2)) { return 1; } 
    if (circleDistance_y <= (rect.height/2)) { return 2; }

    cornerDistance_sq = pow((circleDistance_x - rect.width/2), 2.0)+ pow((circleDistance_y - rect.height/2), 2.0);

    return (cornerDistance_sq <= pow(radius,2.0));
}
