#pragma once

#include <engine/Material.h>
#include <engine/Object.h>

#include <GL/glew.h>

class Mesh
{
public:
	Mesh(unsigned int, unsigned int, float *, float *, unsigned int *, float * = NULL);
	~Mesh();

	unsigned int vao;

	unsigned int numberOfVertices;
	float *vertices;
	float *normals;
	float *textureCoords;

	unsigned int numberOfIndices;
	unsigned int *indices;

	struct bounds
	{
		float minx, miny, minz;
		float maxx, maxy, maxz;
	}bounds;

	void loadMesh();
	void bind();
	void unbind();
	void render();
	void freeMesh();

private:


	void createVAO();
	void storeData(int attribID, int num, GLenum target, GLenum type, void * buffer, int size, bool isIndices = false);
	



};

