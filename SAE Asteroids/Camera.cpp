#include "Camera.h"

Camera::Camera()
{
}

Camera::Camera(glm::vec3 cameraPos, glm::vec3 cameraTarget, glm::vec3 upVector)
{
	cameraPosition = cameraPos;
	cameraDirection = glm::normalize(cameraPosition - cameraTarget);
	glm::vec3 cameraRight = glm::normalize(glm::cross(upVector, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
}


Camera::~Camera()
{
}

void Camera::CameraPosition(glm::vec3 CameraPos)
{
	cameraPosition = CameraPos;
}

void Camera::CameraDirection(glm::vec3 cameraTarget)
{
	cameraDirection = glm::normalize(cameraPosition - cameraTarget);
}

void Camera::CameraUp(glm::vec3 up)
{
	glm::vec3 cameraRight = glm::normalize(glm::cross(up, cameraDirection));
	cameraUp = glm::cross(cameraDirection, cameraRight);
}

glm::mat4 Camera::GetMVP() {
	return this->projection * this->view;
}