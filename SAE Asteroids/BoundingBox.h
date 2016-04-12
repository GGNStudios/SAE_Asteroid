#pragma once

#include <glm.hpp>
#include <vector>
#include "Mesh.h"

#define		NUM_VERTEX		4
#define		M_PI			3.14159265

using namespace glm;

class BoundingBox
{
public:
	BoundingBox();
	BoundingBox(Vertex* vertices);
	~BoundingBox();

	bool CheckCollisions(BoundingBox b);
	void UpdateBB(float angle);
	void BoundingBox::DrawBB();

private:
	std::vector <vec2> bbVertex;
	std::vector <vec2> bbVertexTransformed;

	std::vector<vec2> calcBBVertex(std::vector<vec3> vertices);
	std::vector<vec2> calcTransformedBBVertex(std::vector<vec3> vertices, float angle);

};

