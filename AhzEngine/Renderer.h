#pragma once

#include "DeviceResources.h"
#include "Box.h"
#include "MeshComponent.h"
#include <vector>

class Renderer
{
public:
	bool IsInitialized() const noexcept;
	void Init(DeviceResources*) noexcept;
	void Shutdown() noexcept;
	void Render();
	DeviceResources* pDeviceResources = nullptr;
	std::vector<MeshComponent*> meshes;
};

