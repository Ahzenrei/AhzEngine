#pragma once

#include <vector>
#include "MeshComponent.h"
#include "AhzMath.h"
#include <DirectXMath.h>
#include <unordered_map>

class SceneElement
{
public:
	void AddComponent(Component * component) noexcept;
	bool HasComponent(Component::ComponentType) const noexcept;
	Component* GetComponent(Component::ComponentType) noexcept;

private:
	std::unordered_map<Component::ComponentType, Component*> components;
};

