#pragma once
#ifndef TRACER_H
#define TRACER_H

#include <GLM/glm.hpp>
#include "Ray.h"

class Tracer
{
public:
	Tracer();
	~Tracer();

	glm::vec3 TraceRay(Ray raymond);

private:

};

#endif // !TRACER_H
