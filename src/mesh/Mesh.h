#pragma once

#include <stdlib.h>

class Mesh {
	unsigned int VAO;
	unsigned int VBO;
	unsigned int extraVbo;
	size_t vertexSize;
	size_t vertices;
	const int* attrs;
public:
	Mesh(const float* buffer, size_t vertices, const int* attrs);
	Mesh(const float* verBuffer, const float* buffer, size_t ververtices, size_t vertices, const int* attrs);
	~Mesh();

	int amount;

	void draw(unsigned int primetive);
	void draw(unsigned int primetive, int ver);

	void reload(const float* buffer, size_t vertices);
};