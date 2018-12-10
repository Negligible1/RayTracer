#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera
{
public:
	Camera();
	~Camera();

	Ray ReturnRay(int x, int y, int height, int width);

private:
	glm::mat4 ViewMatrix;
	glm::mat4 ProjMatrix;

};

#endif // !CAMERA_H
