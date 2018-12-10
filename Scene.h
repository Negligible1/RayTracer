#pragma once
#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>

#include "Sphere.h"

class Scene
{
public:
	std::vector<std::shared_ptr<Sphere>> sphereInScene;

};

#endif // !SCENE_H
