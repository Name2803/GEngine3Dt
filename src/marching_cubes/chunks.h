#pragma once

class Chunk;
class Marching_cubes;

#include <stdlib.h>

class Chunks {
public:
	Chunk** chunks;
	size_t volume;
	unsigned int w, h, d;

	Chunks(int w, int h, int d);
	~Chunks();
};