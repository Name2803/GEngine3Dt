#include "chunk.h"

#include "marching_cubes.h"
#include "chunks.h"

#include "../graphics/ShaderCl.h"
#include "../mesh/Mesh.h"

#include <math.h>
#include <random>
#include <glm/glm.hpp>
#include <glm/gtc/noise.hpp>

Chunk::Chunk(int xpos, int ypos, int zpos, Chunks* chunks, int temp):
	xpos(xpos), ypos(ypos), zpos(zpos)
{

	shouldToDraw = false;
	/*std::cout << xpos << "\t" << ypos << "\t" << zpos << "\n";*/
	int Y;
	marching_cubes = new Marching_cubes[CHUNK_D * CHUNK_H * CHUNK_W];
	for (int y = 0; y < CHUNK_H; y++) {
		for (int z = 0; z < CHUNK_D; z++) {
			for (int x = 0; x < CHUNK_W; x++) {
				
				
				
				/*if (x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y < 256)
					marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind = x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y;
				else
					if(y == 1)
						if(z == 0)
							marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind = 0;
						else
							marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind = 15;
					else
						marching_cubes[x + (CHUNK_W * z) + CHUNK_W * CHUNK_D * y].mc_ind = 0;
				continue;*/
				
				int real_x = x + xpos * CHUNK_W;
				int real_z = z + zpos * CHUNK_D;
				int real_y = y + ypos * CHUNK_H;
				float height = glm::perlin(glm::vec3(real_x * 0.07f, real_z * 0.07f, real_y * 0.07f)) * 10 + 5;
				int id = glm::perlin(glm::vec3(real_x * 0.0325f, real_y * 0.0625f, real_z * 0.0325f)) > 0.1f;
				if (!id) { continue; }
				//--------------------------------------------------------------------------- v.1.2
				//chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y + z) + x].textureID = 1;
				if (y == 0)
				{
					if (z == 0)
					{
						if (x == 0)
						{

							marching_cubes[0].mc_ind |= 1;
							//close the void between chunks=================begin======zero=point
							if (ypos == 0)
							{
								if (zpos == 0)
								{
									if (xpos != 0)
									{
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W - 1].mc_ind |= 2;
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->d * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D - 1)].mc_ind |= 8;
									}
									else
									{
										chunks->chunks[chunks->d * zpos + xpos - 1]->marching_cubes[CHUNK_W - 1].mc_ind |= 2;
										chunks->chunks[chunks->d * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D - 1)].mc_ind |= 8;
										chunks->chunks[chunks->d * (zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_W - 1].mc_ind |= 4;
									}
								}
							}
							else
							{
								if (zpos == 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1)].mc_ind |= 16;
									}
									else
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1)].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + CHUNK_W - 1].mc_ind |= 32;
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D - 1)].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1)].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1)]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - CHUNK_W].mc_ind |= 128;
									}
									else
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D - 1)].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1)].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + CHUNK_W - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - CHUNK_W].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========
						}
						else
						{
							marching_cubes[x].mc_ind |= 1;
							marching_cubes[x - 1].mc_ind |= 2;
							//close the void between chunks=================begin______x_line
							if (ypos == 0)
							{
								if (zpos != 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[(zpos - 1) * chunks->w]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x].mc_ind |= 8;
										chunks->chunks[(zpos - 1) * chunks->w]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x - 1].mc_ind |= 4;
									}
									else
									{
										chunks->chunks[(zpos - 1) * chunks->w + xpos]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x].mc_ind |= 8;
										chunks->chunks[(zpos - 1) * chunks->w + xpos]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x - 1].mc_ind |= 4;
									}
								}
							}
							else
							{
								if (zpos == 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x - 1].mc_ind |= 32;
									}
									else
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x - 1].mc_ind |= 32;
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1)]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - CHUNK_W + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1)]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - CHUNK_W + x - 1].mc_ind |= 64;
									}
									else
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D - 1) + x - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * (CHUNK_H - 1) + x - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - CHUNK_W + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos - 1) + xpos]->marching_cubes[CHUNK_W * CHUNK_D * CHUNK_H - CHUNK_W + x - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========
						}
					}
					else
					{
						if (x == 0)
						{
							marching_cubes[z * CHUNK_W].mc_ind |= 1;
							marching_cubes[(z - 1) * CHUNK_W].mc_ind |= 8;
							//close the void between chunks=================begin_____z_line
							if (ypos == 0)
							{
								if (zpos == 0)
								{
									if (xpos != 0)
									{
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (z + 1) - 1].mc_ind |= 2;
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (z)-1].mc_ind |= 4;
									}
								}
								else
								{
									if (xpos != 0)
									{
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (z + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * z - 1].mc_ind |= 4;
									}
								}
							}
							else
							{
								if (zpos == 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z)].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1)].mc_ind |= 128;
									}
									else
									{
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (z + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * z - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z)].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1)].mc_ind |= 128;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) - 1].mc_ind |= 64;
										//------------stuck-hear-----------------------------------
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z)].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1)].mc_ind |= 128;
									}
									else
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (z + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * z - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z)].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1)].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========
						}
						else
						{
							marching_cubes[z * CHUNK_W + x].mc_ind |= 1;
							marching_cubes[z * CHUNK_W + x - 1].mc_ind |= 2;
							marching_cubes[(z - 1) * CHUNK_W + x].mc_ind |= 8;
							marching_cubes[(z - 1) * CHUNK_W + x - 1].mc_ind |= 4;
							//close the void between chunks=================begin_____x_z_surface
							if (ypos != 0)
							{
								if (zpos == 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x - 1].mc_ind |= 64;
									}
									else
									{
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * chunks->d * (ypos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x - 1].mc_ind |= 64;
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos)]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x - 1].mc_ind |= 64;
									}
									{
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x].mc_ind |= 16;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z) + x - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * (ypos - 1) + zpos) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (CHUNK_H - 1) + z - 1) + x - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========
						}
					}
				}
				else {
					if (z == 0)
					{
						if (x == 0)
						{
							marching_cubes[CHUNK_W * CHUNK_D * y].mc_ind |= 1;
							marching_cubes[CHUNK_W * CHUNK_D * (y - 1)].mc_ind |= 16;

							//close the void between chunks=================begin_____y_line
							if (ypos == 0)
							{
								if (zpos == 0)
								{
									if (xpos != 0)
									{
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + 1) - 1].mc_ind |= 2;
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + 1) - 1].mc_ind |= 32;
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1)].mc_ind |= 8;
										chunks->chunks[chunks->w * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1)].mc_ind |= 128;
									}
									else
									{
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1)].mc_ind |= 8;
										chunks->chunks[chunks->w * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1)].mc_ind |= 128;
										chunks->chunks[chunks->w * (zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * (y + 1) - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * y - 1].mc_ind |= 64;
									}
								}
							}
							else
							{
								if (zpos == 0)
								{
									if (xpos != 0)
									{
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + 1) - 1].mc_ind |= 32;
									}
								}
								else
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1)].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1)].mc_ind |= 128;
									}
									else
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1)].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1)].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * (y + 1) - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos - 1]->marching_cubes[CHUNK_W * CHUNK_D * y - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========

						}
						else
						{
							marching_cubes[CHUNK_W * CHUNK_D * y + x].mc_ind |= 1;
							marching_cubes[CHUNK_W * CHUNK_D * y + x - 1].mc_ind |= 2;
							marching_cubes[CHUNK_W * CHUNK_D * (y - 1) + x].mc_ind |= 16;
							marching_cubes[CHUNK_W * CHUNK_D * (y - 1) + x - 1].mc_ind |= 32;

							//close the void between chunks=================begin_____x_y_surface
							if (ypos == 0)
							{
								if (zpos != 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x].mc_ind |= 8;
										chunks->chunks[chunks->w * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x - 1].mc_ind |= 64;
									}
									else
									{
										chunks->chunks[chunks->w * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x].mc_ind |= 8;
										chunks->chunks[chunks->w * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x - 1].mc_ind |= 64;
									}
								}
							}
							else
							{
								if (zpos != 0)
								{
									if (xpos == 0)
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1)]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x - 1].mc_ind |= 64;
									}
									else
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x].mc_ind |= 8;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * (y + 1) - 1) + x - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x].mc_ind |= 128;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos - 1) + xpos]->marching_cubes[CHUNK_W * (CHUNK_D * y - 1) + x - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========
						}
					}
					else
					{
						if (x == 0)
						{
							marching_cubes[CHUNK_W * (CHUNK_D * y + z)].mc_ind |= 1;
							marching_cubes[CHUNK_W * (CHUNK_D * y + z - 1)].mc_ind |= 8;
							marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z)].mc_ind |= 16;
							marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z - 1)].mc_ind |= 128;

							//close the void between chunks=================begin_____y_z_surface
							if (ypos == 0)
							{
								if (zpos == 0)
								{
									if (xpos != 0)
									{
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z + 1) - 1].mc_ind |= 2;
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z) - 1].mc_ind |= 4;
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z + 1) - 1].mc_ind |= 32;
										chunks->chunks[xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z) - 1].mc_ind |= 64;
									}
								}
								else
								{
									if (xpos != 0)
									{
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z) - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * zpos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z) - 1].mc_ind |= 64;
									}
								}
							}
							else
							{
								if (zpos == 0)
								{
									if (xpos != 0)
									{
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z) - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * chunks->d * ypos + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z) - 1].mc_ind |= 64;
									}
								}
								else
								{
									if (xpos != 0)
									{
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z + 1) - 1].mc_ind |= 2;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * y + z) - 1].mc_ind |= 4;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z + 1) - 1].mc_ind |= 32;
										chunks->chunks[chunks->w * (chunks->d * ypos + zpos) + xpos - 1]->marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z) - 1].mc_ind |= 64;
									}
								}
							}
							//close the void between chunks=================end========
						}
						else
						{
							marching_cubes[CHUNK_W * (CHUNK_D * y + z) + x].mc_ind |= 1;
							marching_cubes[CHUNK_W * (CHUNK_D * y + z) + x - 1].mc_ind |= 2;
							marching_cubes[CHUNK_W * (CHUNK_D * y + z - 1) + x].mc_ind |= 8;
							marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z) + x].mc_ind |= 16;
							marching_cubes[CHUNK_W * (CHUNK_D * y + z - 1) + x - 1].mc_ind |= 4;
							marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z) + x - 1].mc_ind |= 32;
							marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z - 1) + x].mc_ind |= 128;
							marching_cubes[CHUNK_W * (CHUNK_D * (y - 1) + z - 1) + x - 1].mc_ind |= 64;
						}
					}
				}
				//---------------------------------------------------------------------------
				

				if (!marching_cubes[CHUNK_W * (CHUNK_D * y + z) + x].mc_ind)
				{
					marching_cubes[CHUNK_W * (CHUNK_D * y + z) + x].textureID = 1;
				}
			}
		}
	}
}

Chunk::~Chunk() {
	//delete[] marching_cubes;
}



int Chunk::ChunkBoxDrawer(Shader& chunkBoxShader)
{
	if (shouldToDraw)
	{
		int arts[] = { 3, 3, 0 };
		Mesh chunkBox(l_cube_vert, 24, arts);
		glm::mat4 model = glm::mat4(1.f);
		model = glm::mat4(1.f);
		model = scale(model, glm::vec3(CHUNK_W, CHUNK_H, CHUNK_D));
		model = translate(model, glm::vec3(xpos, ypos, zpos));
		chunkBoxShader.setMat4("model", model);
		chunkBox.draw(GL_LINES);
	}

	return 0;
}