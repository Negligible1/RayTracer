#pragma once
#ifndef TRACER_H
#define TRACER_H

#include <GLM/glm.hpp>
#include <vector>
#include "Ray.h"
#include "Sphere.h"

class Tracer
{
public:
	Tracer();
	~Tracer();

	//quick and dirty
	void AddObject(Sphere *obj) { objects.push_back(obj); }

	glm::vec3 TraceRay(Ray raymond);
	std::vector<Sphere*> objects;

private:

};

#endif // !TRACER_H
