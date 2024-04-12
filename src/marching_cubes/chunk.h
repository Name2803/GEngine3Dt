#pragma once

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

class Marching_cubes;
class Chunks;

class Chunk {
	int amount = CHUNK_VOL;
public:
	int getAmount() { return amount; }
	int x, y, z;
	Marching_cubes* marching_cubes;


	Chunk( int xpos, int ypos, int zpos, Chunks* chunks, int temp);
	~Chunk();
};