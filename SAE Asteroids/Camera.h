#pragma once
#include <glm.hpp>
class Camera
{
public:
	Camera();
	Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 upVector);
	~Camera();

	void CameraPosition(glm::vec3 CameraPos);

	void CameraDirection(glm::vec3 cameraTarget);

	void CameraUp(glm::vec3 up);

	glm::mat4 GetMVP();

	glm::vec3 cameraPosition;
	glm::vec3 cameraDirection;
	glm::vec3 cameraUp;

	glm::mat4 view;
	glm::mat4 projection;
	glm::mat4 model;
};

