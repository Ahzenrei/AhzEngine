#pragma once

#include <vector>
#include "MeshComponent.h"
#include "AhzMath.h"
#include <DirectXMath.h>
#include <unordered_map>

class SceneElement
{
public:
	void AddComponent(Component * component) ;
	bool HasComponent(Component::ComponentType) const ;
	Component* GetComponent(Component::ComponentType) ;

private:
	std::unordered_map<Component::ComponentType, Component*> components;
};

