#include "mesh.h"
#include <map>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <stdlib.h>


Mesh::Mesh()
{

}

Mesh::Mesh(Vertex * vertices, unsigned int numVertices, GLuint program)
{
	m_drawCount = numVertices;
	vertices->numVertices = numVertices;
	
	GLint64 timer;
	glGetInteger64v(GL_TIMESTAMP, &timer);

	timer = 1;

	glm::vec3 position(1,0,0);

	glGenVertexArrays(1, &m_vertexArrayObject);
	glBindVertexArray(m_vertexArrayObject);

	std::vector <glm::vec3> positions;
	std::vector <glm::vec2> textCoords;

	positions.reserve(numVertices);
	textCoords.reserve(numVertices);

	for (unsigned int i = 0; i < numVertices; i++)
	{
		positions.push_back(*vertices[i].GetPos());
		textCoords.push_back(*vertices[i].GetTexCoord());
	}

	//Vertices
	glGenBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[POSITION_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(positions[0]), &positions[0], GL_STATIC_DRAW);

	std::cout << numVertices * sizeof(textCoords[0]) << std::endl;
	std::cout << sizeof(textCoords[0]) << std::endl;

	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

	//Texture
	glBindBuffer(GL_ARRAY_BUFFER, m_vertexArrayBuffers[TEXCOORD_VB]);
	glBufferData(GL_ARRAY_BUFFER, numVertices * sizeof(textCoords[0]), &textCoords[0], GL_STATIC_DRAW);

	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, 0);

	glDrawArrays(GL_TRIANGLES, 0, 3);

	glBindVertexArray(0);
}

Mesh::~Mesh()
{
	//glDeleteBuffers(NUM_BUFFERS, m_vertexArrayBuffers);
	//glDeleteVertexArrays(1, &m_vertexArrayObject);
}

void Mesh::Rotate()
{
	glBindVertexArray(m_vertexArrayObject);

	GLint64 timer;
	glGetInteger64v(GL_TIMESTAMP, &timer);

	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 1, GL_FLOAT, GL_FALSE, 0, 0);

	glBufferData(GL_ARRAY_BUFFER, sizeof(GLint64), &timer, GL_STATIC_DRAW);
	glUniform1f(2, timer / 10000.0);

	glBindVertexArray(0);

}

Vertex* Vertex::VertexConverter(objectInfo object)
{
	int size = object.vertices.size();
	Vertex *v = nullptr;
	v = (Vertex*)malloc(sizeof(Vertex)*size);
	v->numVertices = size;
	for (unsigned int i = 0; i < size; i++)
	{
		v[i].SetPos(object.vertices[i]);
		v[i].SetTexCoord(object.uvs[i]);
	}
	return v;
}

void Mesh::Draw()
{
	glBindVertexArray(m_vertexArrayObject);

	glDrawArrays(GL_TRIANGLES, 0, m_drawCount);

	//glDisableVertexAttribArray(0);
}