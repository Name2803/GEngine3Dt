#pragma once

#include <glm/glm.hpp>

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

	Marching_cubes* get(int x, int y, int z);
	Chunk* getChunk(int x, int y, int z);

	Marching_cubes* rayCast(glm::vec3 a, glm::vec3 dir, float maxDist, glm::vec3& end, glm::vec3& iend);
	void set(int x, int y, int z, int id, int texture_index);
};