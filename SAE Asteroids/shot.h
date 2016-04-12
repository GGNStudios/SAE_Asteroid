#pragma once
#include <glm.hpp>
#include "Entity.h"
#include "Transform.h"

#define		SHOT_SPEED		0.01
#define		BOUND_AREA		1.1

using namespace glm;

class Shot : public Entity
{
public:
	Shot();
	Shot(vec3 pos, vec3 rot, vec3 size, bool enemy, const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex);
	Shot(vec3 pos, vec3 rot, vec3 size, bool enemy, float vel, const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex);

	~Shot();

	void ShotUpdate(Camera cam);
	bool OutOfBounds();
private:
	bool enemyShot; //True when is a enemy shot, false if it's a player shot
	float velocity;
};

