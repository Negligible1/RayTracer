#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <GLM/glm.hpp>
#include "Ray.h"

class Sphere
{
public:
	Sphere();
	~Sphere();

	glm::vec3 ShadePixel(Ray raymond, glm::vec3 Intersect);
	glm::vec3 ClosePointOnLine(Ray raymond, glm::vec3 queryPoint);

	void SphereIntersect(Ray raymond);

	bool hit;
	float distanceToHit;

private:
	int radius;
	glm::vec3 centre;
};


#endif // !SPHERE_H
