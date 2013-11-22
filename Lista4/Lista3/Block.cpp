#include "Block.h"


Block::Block(float x, float y)
{
	drawmode = 6; // GL_TRIANGLE_FAN
	vertexsize = 4;
	height = 0.14;
	width = 0.235;

	changevector[0] = x;
	changevector[1] = y;
}