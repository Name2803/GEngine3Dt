#include "Mesh.h"
#include <glad/glad.h>




Mesh::Mesh(const float* buffer, size_t vertices, const int* attrs) :
	vertices(vertices),
	attrs(attrs)
{

	vertexSize = 0;
	for (int i = 0; attrs[i]; i++) {
		vertexSize += attrs[i];
	}

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);

	// attributes
	int offset = 0;
	for (int i = 0; attrs[i]; i++) {
		int size = attrs[i];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertexSize * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += size;
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
}

Mesh::Mesh(const float* verBuffer, const float* buffer, size_t ververtices, size_t vertices, const int* attrs) 
	: vertices(ververtices * 3)
{
	int vertex_size = 0;
	for (int i = 0; attrs[i]; i++) {
		vertex_size += attrs[i];
	}
	amount = ververtices;

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glGenBuffers(1, &extraVbo);

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, extraVbo);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * ververtices * 3, verBuffer, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertex_size * vertices, buffer, GL_STATIC_DRAW);

	// attributes
	int offset = 0;
	for (int i = 1; attrs[i - 1]; i++) {
		int size = attrs[i - 1];
		glVertexAttribPointer(i, size, GL_FLOAT, GL_FALSE, vertex_size * sizeof(float), (GLvoid*)(offset * sizeof(float)));
		glEnableVertexAttribArray(i);
		offset += attrs[i - 1];
	}
	glBindVertexArray(0);
}


Mesh::~Mesh() {
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
}


void Mesh::draw(unsigned int primetive) {
	glBindVertexArray(VAO);
	glDrawArrays(primetive, 0, vertices);
	glBindVertexArray(0);
}

void Mesh::draw(unsigned int primetive, int ver) {
	glBindVertexArray(VAO);
	glDrawArrays(primetive, 0, ver);
	glBindVertexArray(0);
}

void Mesh::reload(const float* buffer, size_t vertices) {

	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertexSize * vertices, buffer, GL_STATIC_DRAW);
	this->vertices = vertices;
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}