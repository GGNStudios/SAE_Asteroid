#pragma once
#include "Entity.h"

# define M_PI           3.14159265358979323846

#define		TIME_TO_RELOAD			10
#define		MAX_SPEED				0.1
#define		SPEED_INCREMENT			0.001

class Player : public Entity
{
public:
	Player();
	Player(const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex);
	~Player();

	void Update();

	void PlayerMovement();

	bool IsMovingForward(bool check);
	bool IsMovingBackward(bool check);
	bool IsMovingRightward(bool check);
	bool IsMovingLeftward(bool check);

	float GetVelocity() { return (speed.x * speed.y); }

private:
	float counter;
	unsigned int health;
	glm::vec2 speed;
	bool movingForward;
	bool movingBackward;
	bool movingRightward;
	bool movingLeftward;
};

