#pragma once
#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

class Camera
{
public:
	Camera();
	~Camera();

	Ray ReturnRay(int x, int y);

private:

};

#endif // !CAMERA_H
