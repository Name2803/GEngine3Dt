#pragma once

#include <stdlib.h>

class Mesh {
	unsigned int vao;
	unsigned int vbo;
	unsigned int extraVbo;
	size_t vertices;
public:
	Mesh(const float* buffer, size_t vertices, const int* attrs);
	Mesh(const float* verBuffer, const float* buffer, size_t ververtices, size_t vertices, const int* attrs);
	~Mesh();

	int amount;

	void draw(unsigned int primetive);
	void draw(unsigned int primetive, int ver);
};