#pragma once
#ifndef RAY_H
#define RAY_H

#include <GLM/glm.hpp>

class Ray
{
public:
	Ray();
	~Ray();

	void setOrigin(glm::vec3 _origin) { origin = _origin; }
	void setDirection(glm::vec3 _direction) { direction = _direction; }

	glm::vec3 origin;
	glm::vec3 direction;

private:
};

#endif // !RAY_H
