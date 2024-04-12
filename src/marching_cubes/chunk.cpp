#include "chunk.h"

#include "marching_cubes.h"
#include "chunks.h"

#include <math.h>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

Chunk::Chunk(int xpos, int ypos, int zpos, Chunks* chunks, int temp):
	x(xpos), y(ypos), z(zpos)
{
	int Y;
	marching_cubes = new Marching_cubes[CHUNK_D * CHUNK_H * CHUNK_W];
	for (int y = 0; y <= CHUNK_H; y++) {
		for (int z = 0; z <= CHUNK_D; z++) {
			for (int x = 0; x <= CHUNK_W; x++) {
				//marching_cubes[x + (CHUNK_W * z) * CHUNK_D * y].ind;
				if (1) {
					int real_x = x + xpos * CHUNK_W;
					int real_z = z + zpos * CHUNK_D;
					int real_y = y + ypos * CHUNK_H;
					float height = glm::perlin(glm::vec3(real_x * 0.05f, real_z * 0.05f, real_y * 0.05f)) * 10;

					if (y < height) continue;
				}
				else {
					if (y < (sin(x * 0.6) * 0.5 + 0.5) * 3.0f && y < (sin(z * 0.6) * 0.5 + 0.5) * 3.0f) continue;
				}
				//---------------------------------------------------------------------------
				if (x != 0) {
					if (z != 0) {
						if (y != 0) {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
							}
							if (x == CHUNK_W) {
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
								if (z == CHUNK_D) {
									marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
									marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
									if (y == CHUNK_H) {
										marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
									}
								}
								if (y == CHUNK_H) {
									marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
									marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
								}
							}
							if (z == CHUNK_D) {
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
								if (y == CHUNK_H) {
									marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
									marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
								}
							}
							if (y == CHUNK_H && z != CHUNK_D && x != CHUNK_W) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 64;
							}
						}
						else {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
							}
							if (x == CHUNK_W) {
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
								if (z == CHUNK_D) {
									marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
								}
							}
							if (z == CHUNK_D) {
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
								marching_cubes[x - 1 + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 4;
							}
						}
					}
					else {
						if (y != 0) {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
							}
							if (x == CHUNK_W) {
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
								if (y == CHUNK_H) {
									marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
								}
							}
							if (y == CHUNK_H) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 32;
							}
						}
						else {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
							}
							if (x == CHUNK_W) {
								marching_cubes[x - 1 + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 2;
							}
						}
					}
				}
				else {
					if (z != 0) {
						if (y != 0) {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
							}
							if (z == CHUNK_D) {
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
								if (y == CHUNK_H) {
									marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
								}
							}
							if (y == CHUNK_H) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 128;
							}
						}
						else {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
							}
							if (z == CHUNK_D) {
								marching_cubes[x + (CHUNK_W * (z - 1)) + CHUNK_W * CHUNK_D * y].mc_ind |= 8;
							}
						}
					}
					else {
						if (y != 0) {
							if (x != CHUNK_W && z != CHUNK_D && y != CHUNK_D) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
							}
							if (y == CHUNK_H) {
								marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;
							}
						}
						else {
							marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind |= 1;
						}
					}
				}
				//---------------------------------------------------------------------------
				
			}
		}
	}
}

Chunk::~Chunk() {
	//delete[] marching_cubes;
}