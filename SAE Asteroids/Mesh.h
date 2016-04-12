#pragma once
#include <GL/glew.h>
#include <glm.hpp>
#include <string>
#include <vector>
#include "ObjLoader.h"

class Vertex
{
public:

	int numVertices;

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord, const glm::vec3& normal)
	{
		this->pos = pos;
		this->texCoord = texCoord;
		this->normal = normal;
	}

	Vertex(const glm::vec3& pos)
	{
		this->pos = pos;
	}

	Vertex(const glm::vec3& pos, const glm::vec2& texCoord)
	{
		this->pos = pos;
		this->texCoord = texCoord;
	}

	glm::vec3* GetPos() { return &pos; }
	glm::vec2* GetTexCoord() { return &texCoord; }
	glm::vec3* GetNormal() { return &normal; }

	void SetPos(glm::vec3 pos) { this->pos = pos; }
	void SetTexCoord(glm::vec2 coord) { this->texCoord = coord; }
	void SetNormal(glm::vec3 normal) { this->normal = normal; }

	Vertex* VertexConverter(objectInfo object);

private:
	glm::vec3 pos;
	glm::vec2 texCoord;
	glm::vec3 normal;
};

/*enum MeshBufferPositions
{
	POSITION_VB,
	TEXCOORD_VB,
	NORMAL_VB,
	INDEX_VB
};*/

class Mesh
{
public:
	Mesh();

	Mesh(Vertex* vertices, unsigned int numVertices, GLuint program);

	void Draw();

	virtual ~Mesh();
	void Rotate();
protected:
private:
	//static const unsigned int NUM_BUFFERS = 4;
	//void operator=(const Mesh& mesh);
	//Mesh(const Mesh& mesh);

	enum {
		POSITION_VB,
		TEXCOORD_VB,
		POSITION,
		ROTATION,
		NUM_BUFFERS
	};

	GLuint m_vertexArrayObject;
	GLuint m_vertexArrayBuffers[NUM_BUFFERS];
	GLuint m_colorArrayBuffers[NUM_BUFFERS];
	unsigned int m_drawCount;
};

