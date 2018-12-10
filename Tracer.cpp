#include "Tracer.h"
#include "Scene.h"

#include <mutex>

std::mutex mtx2;

Tracer::Tracer()
{
}

Tracer::~Tracer()
{
}

glm::vec3 Tracer::TraceRay(Ray raymond)
{
	mtx2.lock(); //necessary but makes it slow, need to find better solution
	std::vector<Sphere*> hitObjs;
	glm::vec3 returnColour;

	for each (Sphere *var in objects)
	{
		var->SphereIntersect(raymond);
		if (var->hit)
		{
			hitObjs.push_back(var);
		}
	}

	Sphere *closestHit = nullptr;
	bool first = false;

	for each (Sphere *var in hitObjs)
	{
		if(!first)
		{
			closestHit = var;
			first = true;
		}
		else
		{
			if ((closestHit->distanceToHit > var->distanceToHit))
			{
				closestHit = var;
			}
		}
	}

	if (closestHit)
	{
		returnColour = closestHit->ShadePixel();
	}
	else
	{
		returnColour = glm::vec3(0, 0, 0);
	}
	mtx2.unlock();
	return returnColour;
}