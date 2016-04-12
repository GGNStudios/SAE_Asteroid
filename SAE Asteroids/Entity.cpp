#include "Entity.h"



Entity::Entity()
{
}

Entity::Entity(const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex)
{
	shader = Shader(ShaderFile, shaderProgram);
	ObjLoader obj = ObjLoader(Meshfile);
	Vertex v = Vertex(glm::vec3(0, 0, 0));
	model = Mesh(v.VertexConverter(obj.obj), obj.obj.vertices.size(), shaderProgram);
	BoundingBox bb(v.VertexConverter(obj.obj));
	boundingBox = bb;
	m_program = shaderProgram;
	m_texture = textureIndex;
}


Entity::~Entity()
{
}

void Entity::EntityMovementP(glm::vec3 position)
{
	transform.GetPos() = position;
}

void Entity::EntityMovementR(glm::vec3 rotation)
{
	transform.GetRot() = rotation;
}

void Entity::EntityMovementPR(glm::vec3 position, glm::vec3 rotation)
{
	transform.GetPos() = position;
	transform.GetRot() = rotation;
}

void Entity::EntityScaling(glm::vec3 scale)
{
	transform.GetScale() = scale;
}

void Entity::MeshDiffuseTextureLoader(const char * DiffTexturePath)
{
	diffuseTexture = Texture(DiffTexturePath, m_texture);
	diffuseTexture.Bind(m_texture,m_texture);
}

void Entity::MeshRasterization(Camera cam)
{
	boundingBox.DrawBB();
	shader.Bind(m_program);
	diffuseTexture.Bind(m_texture, m_texture);
	shader.Update(this->transform, cam);
	model.Draw();
}

void Entity::UpdateBoundingBox(float angle)
{
	boundingBox.UpdateBB(angle);
}
