#include "Sphere.h"
#include <iostream>

Sphere::Sphere(glm::vec3 _position, float _radius)
{
	centre = _position;
	radius = _radius;
	radius2 = _radius * _radius;
}

Sphere::~Sphere()
{
}

glm::vec3 Sphere::ShadePixel()
{
	return colour;
}


bool Sphere::ClosePointOnLine(Ray raymond, glm::vec3 queryPoint, float&t0, float&t1)
{
	//Calc distance from ray to the objects centre point
	glm::vec3 fromROrgtoSCentre = centre - raymond.origin;
	bool ahead = true;
	bool hit = true;

	//Checks the amount of travel the ray must do to be "inline" with the centre of our object
	float rayTravelDistance = glm::dot(fromROrgtoSCentre, raymond.direction);
	//if this is less than 0 its behind us
	if (rayTravelDistance < 0)
	{
		ahead = false;
	}

	if (ahead)
	{
		//Hit check
		float RTDTimesItself = rayTravelDistance * rayTravelDistance;
		float FROTSCDot = glm::dot(fromROrgtoSCentre, fromROrgtoSCentre);

		float d2 = FROTSCDot - RTDTimesItself;
		if (d2 > radius2)
		{
			hit = false;
		}


		if (hit)
		{
			//Hit point
			float thc = glm::sqrt(radius2 - d2);
			t0 = rayTravelDistance - thc;
			t1 = rayTravelDistance + thc;
			return hit;
		}
	}
}

void Sphere::SphereIntersect(Ray raymond)
{
	bool skip = false;
	hit = false;
	glm::vec3 intersectionPoint;

	//Check if ray origin is inside sphere
	
	if (raymond.origin.x <= centre.x + radius && raymond.origin.x >= centre.x - radius)
	{
		if (raymond.origin.y <= centre.y + radius && raymond.origin.y >= centre.y - radius)
		{
			if (raymond.origin.z <= centre.z + radius && raymond.origin.z >= centre.z - radius)
			{
				//If we made it here that means our Ray's origin is inside the sphere, therefore we treat it as an error and do nothing, so skip comes into play
				hit = false;
				skip = true;
			}
		}
	}

	if (!skip)
	{
		float tnear = INFINITY;
		float t0 = INFINITY, t1 = INFINITY;
		if (ClosePointOnLine(raymond, centre, t0, t1))
		{
			if (t0 < 0)
			{
				t0 = t1;
			}
			if (t0 < tnear)
			{
				tnear = t0;
				hit = true;
			}
		}
		 
		glm::vec3 nhit;
		glm::vec3 phit;
		if (hit)
		{
			phit = raymond.origin + raymond.direction * tnear;
			nhit = phit - centre;
			glm::normalize(nhit);
			intersectionPoint = phit;

			//defines a lightsource, bad need to move it make it permanent across the scene
			//glm::vec3 lightsource = glm::vec3(640 / 2, 0, -1000);

			//direction from sample point to light
			//glm::vec3 lightDir = glm::normalize(phit - lightsource);
			
			//glm::vec3 diffuse = colour * glm::vec3(1, 1, 1) * glm::max(glm::dot(nhit, lightDir), 0.0f);

			//colour = diffuse;

			//L light hits camera
			//wi light vector
			//n surface normal
			//li light colour
			//kd is material diffuse colour
		}
	}
}