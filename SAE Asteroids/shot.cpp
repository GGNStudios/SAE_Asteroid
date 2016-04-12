#include "shot.h"

Shot::Shot()
{
	transform.GetPos() = vec3(0,0,0);
	transform.GetRot() = vec3(0, 0, 0);
	transform.GetScale() = vec3(0, 0, 0);

	enemyShot = false;

	velocity = SHOT_SPEED;
}

Shot::Shot(vec3 pos, vec3 rot, vec3 size, bool enemy, const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex) : Entity(Meshfile,ShaderFile,shaderProgram,textureIndex)
{
	transform.GetPos() = pos;
	transform.GetRot() = rot;
	transform.GetScale() = size;

	enemyShot = enemy;

	velocity = SHOT_SPEED;
}

Shot::Shot(vec3 pos, vec3 rot, vec3 size, bool enemy, float vel, const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex) : Entity(Meshfile, ShaderFile, shaderProgram, textureIndex)
{
	transform.GetPos() = pos;
	transform.GetRot() = rot;
	transform.GetScale() = size;

	enemyShot = enemy;

	velocity = vel;
}

Shot::~Shot()
{

}

void Shot::ShotUpdate(Camera cam)
{
	float angle = transform.GetRot().z;
	transform.GetPos() += vec3( velocity * cos(angle) , velocity * sin(angle), 0 );
	MeshRasterization(cam);
}

bool Shot::OutOfBounds()
{
	if (abs(transform.GetPos().x) > BOUND_AREA || abs(transform.GetPos().y) > BOUND_AREA)
		return true;
	else
		return false;
}
