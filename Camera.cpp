#include "Camera.h"

Camera::Camera()
{

}

Camera::~Camera()
{

}

Ray Camera::ReturnRay(int x, int y, int height, int width)
{
	Ray raymond;
	
	glm::vec3 rayOrigin = glm::vec3(x, y, 0); //glm::vec3((x + (-height / 2)), (y + (-width / 2)), 0);
	glm::vec3 rayDirection = glm::vec3(0, 0, -1);

	raymond.setOrigin(rayOrigin);
	raymond.setDirection(rayDirection);

	return raymond;
}