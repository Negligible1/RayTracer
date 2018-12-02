#include "Sphere.h"

Sphere::Sphere()
{
}

Sphere::~Sphere()
{
}

glm::vec3 Sphere::ShadePixel(Ray raymond, glm::vec3 Intersect)
{
	return glm::vec3(1, 0, 0);
}


glm::vec3 Sphere::ClosePointOnLine(Ray raymond, glm::vec3 queryPoint)
{
	glm::vec3 X = glm::vec3(0, 0, 0);
	X = raymond.origin + ((queryPoint - raymond.origin) ^ raymond.direction) * raymond.direction;
	return X;
}

void Sphere::SphereIntersect(Ray raymond)
{
	bool skip = false;

	if (raymond.origin.x <= centre.x + radius && raymond.origin.x >= centre.x - radius)
	{
		if (raymond.origin.y <= centre.y + radius && raymond.origin.y >= centre.y - radius)
		{
			if (raymond.origin.z <= centre.z + radius && raymond.origin.z >= centre.z - radius)
			{
				hit = false;
				skip = true;
			}
		}
	}

	if (!skip)
	{
		//obtain our closest point as a value
		glm::vec3 closestPoint = ClosePointOnLine(raymond, centre);

		//check the difference between it and the origin and then it and the origin + the direction
		glm::vec3 diff1 = abs(closestPoint - raymond.origin);
		glm::vec3 diff2 = abs(closestPoint - raymond.origin + raymond.direction);

		//check if these values are greater than or equal too
		glm::bvec3 bDiff = glm::greaterThanEqual(diff2, diff1);
		
		//if all the values are true we're facing, otherwise we're not
		if (bDiff == glm::bvec3(true, true, true))
		{
			glm::vec3 distToCentre = closestPoint - centre;

			//

			
		}

		
	}

}