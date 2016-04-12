#pragma once
#include <glm.hpp>
#include "Mesh.h"
#include "Texture.h"
#include "Transform.h"
#include "Shader.h"
#include "BoundingBox.h"

class Entity
{
public:
	Entity();
	Entity(const char* Meshfile, const char* ShaderFile, GLuint shaderProgram, unsigned int textureIndex);

	~Entity();

	void EntityMovementP(glm::vec3 position);
	void EntityMovementR(glm::vec3 rotation);
	void EntityMovementPR(glm::vec3 position, glm::vec3 rotation);
	void EntityScaling(glm::vec3 scale);

	void MeshDiffuseTextureLoader(const char* DiffTexturePath);
	void MeshRasterization(Camera cam);
	void UpdateBoundingBox(float angle);
	Transform transform;
private:
	GLuint m_program;
	unsigned int m_texture;
	Mesh model;
	Shader shader;
	Texture diffuseTexture;
	BoundingBox boundingBox;
};

