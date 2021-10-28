#pragma once

#include <vector>
#include "Component.h"
#include "AhzMath.h"

class SceneElement
{
public:
	SceneElement() noexcept = default;
	~SceneElement() noexcept = default;

private:
	std::vector<Component> components;

	//To do : make a transform class
	Vector3 position = Vector3(0,0,0);
	Vector3 rotation = Vector3(0,0,0);
	Vector3 scale = Vector3(1,1,1);

};

