#pragma once

#define CHUNK_W 16
#define CHUNK_H 16
#define CHUNK_D 16
#define CHUNK_VOL (CHUNK_W * CHUNK_H * CHUNK_D)

class Marching_cubes;
class Chunks;
class Shader;

class Chunk {
public:
	int getAmount() { return amount; }
	int xpos, ypos, zpos;
    int index;
    bool shouldToDraw;
    Marching_cubes* marching_cubes;




	Chunk( int xpos, int ypos, int zpos, Chunks* chunks, int temp);
	~Chunk();

    int ChunkBoxDrawer(Shader& chunkBoxShader);

private:
    int amount = CHUNK_VOL;

    const float l_cube_vert[144] = {
        //vertices      //color
          0.f, 0.f, 0.f,  1.f, 1.f, 1.f,
          0.f, 0.f, 1.f,  0.f, 1.f, 0.f,
          0.f, 0.f, 1.f,  0.f, 1.f, 0.f,
          1.f, 0.f, 1.f,  0.f, 1.f, 1.f,

          1.f, 0.f, 1.f,  0.f, 1.f, 1.f,
          1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
          1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
          0.f, 0.f, 0.f,  1.f, 1.f, 1.f,

          0.f, 0.f, 0.f,  1.f, 1.f, 1.f,
          0.f, 1.f, 0.f,  1.f, 0.f, 0.f,
          0.f, 1.f, 0.f,  1.f, 0.f, 0.f,
          0.f, 1.f, 1.f,  1.f, 1.f, 0.f,

          0.f, 0.f, 1.f,  0.f, 1.f, 0.f,
          0.f, 1.f, 1.f,  1.f, 1.f, 0.f,
          0.f, 1.f, 1.f,  1.f, 1.f, 0.f,
          1.f, 1.f, 1.f,  1.f, 1.f, 1.f,

          1.f, 0.f, 1.f,  0.f, 1.f, 1.f,
          1.f, 1.f, 1.f,  1.f, 1.f, 1.f,
          1.f, 1.f, 1.f,  1.f, 1.f, 1.f,
          1.f, 1.f, 0.f,  1.f, 0.f, 1.f,

          1.f, 0.f, 0.f,  0.f, 0.f, 1.f,
          1.f, 1.f, 0.f,  1.f, 0.f, 1.f,
          1.f, 1.f, 0.f,  1.f, 0.f, 1.f,
          0.f, 1.f, 0.f,  1.f, 0.f, 0.f
    };
};