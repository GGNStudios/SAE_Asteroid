#pragma once

#include <glm.hpp>
#include <vector>
#include <iostream>

struct objectInfo {
	std::vector <glm::vec3> vertices;
	std::vector <glm::vec2> uvs;
	std::vector <glm::vec3> normals;
	int numVertices;
};

void Rescale(std::vector <glm::vec3> &v, float scale);

class ObjLoader
{
public:

	objectInfo obj;

	ObjLoader(const char* path);
	virtual ~ObjLoader();

	bool LoadOBJ(
		const char* path,
		std::vector <glm::vec3> & out_vertices,
		std::vector <glm::vec2> & out_uvs,
		std::vector <glm::vec3> & out_normals
		);

private:

};

