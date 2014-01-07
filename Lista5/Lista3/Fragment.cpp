#include "Fragment.h"

Fragment::Fragment(char *filename)
{
	ifstream binary_data(filename, ios::binary);
	int wspolrzedne = 1442401;
	short * wspolrzedna;
	if (binary_data.is_open())
	{
		wspolrzedna = new short[wspolrzedne];
		binary_data.read(reinterpret_cast<char*>(wspolrzedna), sizeof(short)* wspolrzedne);
		binary_data.close();
	}
	counter = 0;
	for (size_t i = 0; i < 1201; i++)
	{
		for (size_t j = 0; j < 1201; j++)
		{
			//From little-endian to big-endian
			wspolrzedna[counter] = (wspolrzedna[counter] >> 8) | (wspolrzedna[counter] << 8);
			// cout << wspolrzedna[counter] << " ";
			counter++;
		}
	}

	vector<vec3> vectors;
	counter = 1;

	for (size_t j = 0; j < 1201; j++)
	{
		for (size_t i = 0; i < 1201; i++)
		{
			vectors.push_back(vec3(i*0.1, j*-0.1, wspolrzedna[counter]));
			counter++;
		}
	}

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vectors.size()*sizeof(vec3), vectors.data(), GL_STATIC_DRAW);
	
	generateElementBuffer(10);
}

void Fragment::generateElementBuffer(GLuint LOD)
{
	element_buffer_data.clear();
	for (size_t j = 0; j < 1200 / LOD; j++)
	{
		for (size_t i = 0; i < 1200 / LOD; i++)
		{
			element_buffer_data.push_back(LOD * 0 + (1201 * LOD * j) + (LOD * i));
			element_buffer_data.push_back(LOD * 1 + (1201 * LOD * j) + (LOD * i));
			element_buffer_data.push_back(LOD * 1201 + (1201 * LOD * j) + (LOD * i));
			element_buffer_data.push_back(LOD * 1 + (1201 * LOD * j) + (LOD * i));
			element_buffer_data.push_back(LOD * 1202 + (1201 * LOD * j) + (LOD * i));
			element_buffer_data.push_back(LOD * 1201 + (1201 * LOD * j) + (LOD * i));
		}
	}

	counter = counter / 3;

	// Generate a buffer for the indices as well
	glGenBuffers(1, &elementbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, elementbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, element_buffer_data.size()*sizeof(GLuint), element_buffer_data.data(), GL_STATIC_DRAW);
	elementbuffersize = element_buffer_data.size()*sizeof(GLuint);

}
int Fragment::getCounter()
{
	return counter;
}

GLuint Fragment::getVertexbuffer()
{
	return vertexbuffer;
}

GLuint Fragment::getElementbuffer()
{
	return elementbuffer;
}

GLsizei Fragment::getElementbuffersize()
{
	return elementbuffersize;
}