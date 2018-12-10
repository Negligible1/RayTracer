#pragma once
#ifndef SPHERE_H
#define SPHERE_H

#include <GLM/glm.hpp>
#include "Ray.h"

class Sphere
{
public:
	Sphere(glm::vec3 _position, float _radius);
	~Sphere();

	glm::vec3 ShadePixel();
	glm::vec3 SphereCol;
	bool ClosePointOnLine(Ray raymond, glm::vec3 queryPoint, float&t0, float&t1);

	void SphereIntersect(Ray raymond);

	bool hit;
	float distanceToHit;

	glm::vec3 colour;

	void UpdatePosition(glm::vec3 pos) { centre += pos; }
	glm::vec3 GetPos() { return centre; }

private:
	float radius;
	float radius2;
	glm::vec3 centre;
};


#endif // !SPHERE_H
