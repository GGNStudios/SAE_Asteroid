#include "Player.h"



Player::Player()
{
}

Player::Player(const char * Meshfile, const char * ShaderFile, GLuint shaderProgram, unsigned int textureIndex) : Entity( Meshfile,ShaderFile,shaderProgram,textureIndex)
{
	speed = glm::vec2(0, 0);
	movingBackward = false;
	movingForward = false;
	movingLeftward = false;
	movingRightward = false;
	counter = 0;
}

void Player::Update()
{
	/*transform.GetRot().x = cos(counter)*0.05;
	transform.GetRot().x = -M_PI / 2;
	transform.GetRot().y = sin(counter)*0.1;
	transform.GetRot().z = cos(counter)*0.01;
	counter += 0.01;*/
}


Player::~Player()
{
}

void Player::PlayerMovement()
{
	//Control the speed of the player by the enabled functions
	if (movingBackward || movingForward || movingLeftward || movingRightward) {
		if (movingBackward && abs(speed.x * speed.y) <= MAX_SPEED) {
			speed.x += SPEED_INCREMENT  * sin(transform.GetRot().z);
			speed.y -= SPEED_INCREMENT  * cos(transform.GetRot().z);
		}

		if (movingForward && abs(speed.x * speed.y) <= MAX_SPEED) {
			speed.x -= SPEED_INCREMENT  * sin(transform.GetRot().z);
			speed.y += SPEED_INCREMENT  * cos(transform.GetRot().z);
		}

		if (movingRightward && abs(speed.x * speed.y) <= MAX_SPEED) {
			speed.x += SPEED_INCREMENT  * cos(transform.GetRot().z);
			speed.y += SPEED_INCREMENT  * sin(transform.GetRot().z);
		}

		if (movingLeftward && abs(speed.x * speed.y) <= MAX_SPEED) {
			speed.x -= SPEED_INCREMENT  * cos(transform.GetRot().z);
			speed.y -= SPEED_INCREMENT  * sin(transform.GetRot().z);
		}
	}
	else {
		if (speed.x > SPEED_INCREMENT)
			speed.x -= SPEED_INCREMENT * 2;
		else
			speed.x += SPEED_INCREMENT * 2;

		if (speed.y > SPEED_INCREMENT)
			speed.y -= SPEED_INCREMENT * 2;
		else
			speed.y += SPEED_INCREMENT * 2;
	}

	//Control the stop movement when no inputs are enabled to the player and the epsilon for the total speed is clamped
	if (!movingBackward && !movingForward && !movingLeftward && !movingRightward && abs(speed.x) + abs(speed.y) < SPEED_INCREMENT*10 ) {
		speed = vec2(0,0);
	}

	if (abs(transform.GetPos().x) > 3)
		transform.GetPos().x > 1 ? transform.GetPos().x = 3 : transform.GetPos().x = -3;

	if (abs(transform.GetPos().y) > 3)
		transform.GetPos().y > 1 ? transform.GetPos().y = 3 : transform.GetPos().y = -3;

	transform.GetPos() = glm::vec3(transform.GetPos().x + speed.x, transform.GetPos().y + speed.y, 0);
	std::cout << "PosX = " << transform.GetPos().x << "    PosY = " << transform.GetPos().y << std::endl;
}

bool Player::IsMovingForward(bool check)
{
	movingForward = check;
	return check;
}

bool Player::IsMovingBackward(bool check)
{
	movingBackward = check;
	return check;
}

bool Player::IsMovingRightward(bool check)
{
	movingRightward = check;
	return check;
}

bool Player::IsMovingLeftward(bool check)
{
	movingLeftward = check;
	return check;
}
