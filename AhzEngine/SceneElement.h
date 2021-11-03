#pragma once

#include <vector>
#include "MeshComponent.h"
#include "AhzMath.h"
#include <DirectXMath.h>
#include <unordered_map>

class SceneElement
{
public:

	struct Transform
	{
		DirectX::XMVECTOR  position = { 0,0,0,1 };
		DirectX::XMVECTOR  rotation = { 0,0,0,1 };
		DirectX::XMVECTOR  scale	= { 1,1,1,1 };
	};

	void AddComponent(Component component) noexcept;

	SceneElement() noexcept = default;
	~SceneElement() noexcept = default;

private:
	std::unordered_map<Component::ComponentType,Component> components;
	Transform transform;

};

