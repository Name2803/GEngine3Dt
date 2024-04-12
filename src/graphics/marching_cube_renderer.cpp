#include "marching_cube_renderer.h"

#include "../mesh/Mesh.h"
#include "../marching_cubes/chunk.h"
#include "../marching_cubes/marching_cubes.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

void calculateTriangleNormal(glm::vec3 vertex1, glm::vec3 vertex2, glm::vec3 vertex3, float* vert) {
	glm::vec3 vector1 = vertex2 - vertex1;
	glm::vec3 vector2 = vertex3 - vertex1;

	glm::vec3 normal = glm::cross(vector1, vector2);
	normal = glm::normalize(normal);

	vert[-8 - 10] = 1; vert[-7 - 10] = 1; vert[-6 - 10] = 1;
	vert[-5 - 5] = 1; vert[-4 - 5] = 1; vert[-3 - 5] = 1;
	vert[-2] = 1; vert[-1] = 1; vert[0] = 1;
}

void calculateTriangleTextureCoords(float* p1, float* p2, float* p3) {
	*p1 = 0.0f; p1++; *p1 = 0.0f;
	*p2 = 0.0f; p2++; *p2 = 1.0f;
	*p3 = 1.0f; p3++; *p3 = 1.0f;
}

MarchingCubeRenderer::MarchingCubeRenderer(size_t capacity, int* artts):
	capacity(capacity), artts(artts)
{
	for (int i = 0; artts[i]; i++)
		capacity *= artts[i];
	buffer = new float[capacity];
}

MarchingCubeRenderer::~MarchingCubeRenderer() {
	delete[] buffer;
}

Mesh* MarchingCubeRenderer::render(const Chunk* chunk) {
	float* vertices = buffer;
	int points_quantity = 0;

	for (int y = 0; y < CHUNK_H; y++) {
		for (int z = 0; z < CHUNK_D; z++) {
			for (int x = 0; x < CHUNK_W; x++) {
				int j = 1;
				for (int* verts = &triTable[chunk->marching_cubes[(y * CHUNK_D + z) * CHUNK_W + x].mc_ind][0]; *verts >= 0; j++, verts++) {
					points_quantity++;
					for (int k = 0; k < 8; k++, vertices++) {
						if (k == 0)
							*vertices = vertices_mc[*verts * 3 + k] + x;
						if (k == 1)
							*vertices = vertices_mc[*verts * 3 + k] + y;
						if (k == 2)
							*vertices = vertices_mc[*verts * 3 + k] + z;
						if (k == 3)
							*vertices = vertices_mc[*verts * 3 + 0];
						if (k == 4)
							*vertices = vertices_mc[*verts * 3 + 2];
						if (k == 5)
							*vertices = 1.0f;
						if (k == 6)
							*vertices = 1.0f;
						if (k == 7)
							*vertices = 1.0f;
					}
					/*vertices += 5;
					if (j % 3 == 0) {
						points_quantity++;
						calculateTriangleNormal(glm::vec3(vertices[-8 -15], vertices[-7 - 15], vertices[-6 - 15]),
												glm::vec3(vertices[-5 - 10], vertices[-4 - 10], vertices[-3 - 10]),
												glm::vec3(vertices[-2 - 5], vertices[-1 - 5], vertices[0 - 5]),
												vertices);
						calculateTriangleTextureCoords(&vertices[-6 - 15], &vertices[-3 - 10], &vertices[0 - 5]);
					}*/
				}
			}
		}
	}
	std::cout << points_quantity << "\n";
	return new Mesh(buffer, points_quantity,artts);
}