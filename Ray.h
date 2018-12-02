#pragma once
#ifndef RAY_H
#define RAY_H

#include <GLM/glm.hpp>

class Ray
{
public:
	Ray();
	~Ray();

	glm::vec3 origin;
	glm::vec3 direction;

private:
};

#endif // !RAY_H
