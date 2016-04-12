#include "ObjLoader.h"

ObjLoader::ObjLoader(const char * path)
{
	LoadOBJ(path, obj.vertices, obj.uvs, obj.normals);
}

ObjLoader::~ObjLoader()
{
}

bool ObjLoader::LoadOBJ(const char * path, std::vector<glm::vec3>& out_vertices, std::vector<glm::vec2>& out_uvs, std::vector<glm::vec3>& out_normals)
{
	std::vector< unsigned int > vertexIndices, uvIndices, normalIndices;
	std::vector< glm::vec3 > temp_vertices;
	std::vector< glm::vec2 > temp_uvs;
	std::vector< glm::vec3 > temp_normals;

	FILE* f;
	fopen_s(&f,path, "r");
	if (f == NULL) {
		std::cout << "Unable to open OBJ Archive (Maybe wrong path)" << std::endl;
		return false;
	}
	
	char header[1] = {'\0'}, second[1];
	bool dataSuccess = false;

	double max_size = 0;

	while (feof(f) == 0)
	{
		fscanf_s(f, "%c", header);
		if(header[0] == '\n')
			fscanf_s(f, "%c", header);
		fscanf_s(f, "%c", second);
		
		if (header[0] == 'v' && second[0] == ' ')
		{
			glm::vec3 vertex;
			fscanf_s(f,"%f %f %f\n",&vertex.x, &vertex.y, &vertex.z);
			temp_vertices.push_back(vertex);
			if (abs(vertex.x) > max_size)
				max_size = vertex.x;
			else if (abs(vertex.y) > max_size)
				max_size = vertex.y;
			else if (abs(vertex.z) > max_size)
				max_size = vertex.z;
		}
		else if (header[0] == 'v' && second[0] == 'n')
		{
			glm::vec3 vertex;
			fscanf_s(f, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			temp_normals.push_back(vertex);
		}
		else if (header[0] == 'v' && second[0] == 't')
		{
			glm::vec3 vertex;
			glm::vec2 uv;
			fscanf_s(f, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
			uv.x = vertex.x;
			uv.y = vertex.y;
			temp_uvs.push_back(uv);
			dataSuccess = true;
		}
		else if (header[0] == 'f')
		{
			glm::vec3 vertex,uv,normal;
			fscanf_s(f, "%f/%f/%f %f/%f/%f %f/%f/%f\n", &vertex.x, &uv.x , &normal.x , &vertex.y , &uv.y , &normal.y , &vertex.z , &uv.z, &normal.z);
			vertexIndices.push_back(vertex[0]);
			vertexIndices.push_back(vertex[1]);
			vertexIndices.push_back(vertex[2]);
			uvIndices.push_back(uv[0]);
			uvIndices.push_back(uv[1]);
			uvIndices.push_back(uv[2]);
			normalIndices.push_back(normal[0]);
			normalIndices.push_back(normal[1]);
			normalIndices.push_back(normal[2]);
		}
		else
		{
			char end[1] = { '\0' };

			while (end[0] != '\n' && !feof(f)) {
				fscanf_s(f, "%c", end);
			}
		}
	}

	Rescale(temp_vertices,max_size);

	for (unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		unsigned int vertexIndex = vertexIndices[i];
		glm::vec3 v = temp_vertices[vertexIndex - 1];

		out_vertices.push_back(v);

	}

	obj.numVertices = temp_vertices.size();

	for (unsigned int i = 0; i < uvIndices.size(); i++)
	{
		unsigned int uvIndex = uvIndices[i];
		glm::vec2 u = temp_uvs[uvIndex - 1];
		u.y *= -1;
		out_uvs.push_back(u);
	}

	for (unsigned int i = 0; i < normalIndices.size(); i++)
	{
		unsigned int normalIndex = normalIndices[i];
		glm::vec3 n = temp_normals[normalIndex - 1];

		out_normals.push_back(n);
	}
	return true;

}

void Rescale(std::vector<glm::vec3>& v, float scale)
{
	unsigned int length = v.size();

	for (unsigned int i = 0; i < length; i++)
	{
		v[i] /= scale;
	}
}
