#include "BoundingBox.h"



BoundingBox::BoundingBox()
{
}

BoundingBox::BoundingBox(Vertex *vertices)
{
	if (vertices->numVertices > 0)
	{
		std::vector<vec3> v;
		v.reserve(vertices->numVertices);
		for (unsigned int i = 0; i < vertices->numVertices; i++)
			v.push_back(*vertices[i].GetPos());

		bbVertex = calcBBVertex(v);
		bbVertexTransformed = bbVertex;
	}
}


BoundingBox::~BoundingBox()
{

}

bool BoundingBox::CheckCollisions(BoundingBox b)
{
	/*vec2 normals[] = {	vec2(bbVertexTransformed[1][0].x - bbVertexTransformed[0][0].x, bbVertexTransformed[1][0].y - bbVertexTransformed[0][0].y),
						vec2(bbVertexTransformed[2][0].x - bbVertexTransformed[1][0].x, bbVertexTransformed[2][0].y - bbVertexTransformed[1][0].y),
						vec2(bbVertexTransformed[3][0].x - bbVertexTransformed[2][0].x, bbVertexTransformed[3][0].y - bbVertexTransformed[2][0].y),
						vec2(bbVertexTransformed[0][0].x - bbVertexTransformed[3][0].x, bbVertexTransformed[0][0].y - bbVertexTransformed[3][0].y) };
*/
	bool collision[4] = { true,true,true,true };

	for (unsigned short i = 0; i < b.bbVertexTransformed.size();i++)
	{
		//Dot Product
		float dot = b.bbVertexTransformed[i].x * this->bbVertexTransformed[i].x + b.bbVertexTransformed[i].y * this->bbVertexTransformed[i].y;
		//Det product
		float det = b.bbVertexTransformed[i].y * this->bbVertexTransformed[i].x + b.bbVertexTransformed[i].x * this->bbVertexTransformed[i].y;

		float angle = atan2(det, dot);

		if (cos(angle) < 0)
			collision[i] = false;
	}

	for (unsigned short i = 0; i < 4; i++)
		if (collision[i] == true)
			return true;
	
	return false;
}

void BoundingBox::UpdateBB(float angle)
{
	for (unsigned short i = 0; i < bbVertexTransformed.size(); i++)
	{
		float x = (bbVertex[i].x * cos(angle)) - (bbVertex[i].y * sin(angle));
		float y = (bbVertex[i].x * sin(angle)) + (bbVertex[i].y * cos(angle));
		bbVertexTransformed[i].x = x;
		bbVertexTransformed[i].y = y;
	}
}

void BoundingBox::DrawBB()
{
	glEnable(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	glBegin(GL_LINE_LOOP);
	glLineWidth(10);
	glColor3f(1,0,0);
	glVertex3d(bbVertexTransformed[0].x, 0, bbVertexTransformed[0].y);
	glVertex3d(bbVertexTransformed[1].x, 0, bbVertexTransformed[1].y);
	glVertex3d(bbVertexTransformed[2].x, 0, bbVertexTransformed[2].y);
	glVertex3d(bbVertexTransformed[3].x, 0, bbVertexTransformed[3].y);
	glEnd();
	glPopMatrix();
}

std::vector<vec2> BoundingBox::calcBBVertex(std::vector<vec3> vertices)
{
	if (vertices.size() != 0)
	{
		//Define vectors for v(max,min)
		vec2 x(0,0);
		vec2 y(0,0);
		//Calc x(max,min), y(max,min)
		for (unsigned int i = 0; i < vertices.size(); i++)
		{
			//Max x
			if (vertices[i].x > x.x)
				x.x = vertices[i].x;
			//Min x
			if (vertices[i].x < x.y)
				x.y = vertices[i].x;
			//Max y
			if (vertices[i].y > y.x)
				y.x = vertices[i].y;
			//Min y
			if (vertices[i].y < y.y)
				y.y = vertices[i].y;
		}

		//Calc points from v(min,max), v(max,max), v(max, min), v(min,min)
		std::vector<vec2> bbVertex;
		bbVertex.reserve(4);

		bbVertex.push_back(vec2(x.y, y.x));
		bbVertex.push_back(vec2(x.x, y.x));
		bbVertex.push_back(vec2(x.x, y.y));
		bbVertex.push_back(vec2(x.y, y.y));

		return bbVertex;
	}
	else
		return std::vector<vec2>();
}

std::vector<vec2> BoundingBox::calcTransformedBBVertex(std::vector<vec3> vertices, float angle)
{
	return std::vector<vec2>();
}

