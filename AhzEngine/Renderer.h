#pragma once

#include "DeviceResources.h"
#include "Box.h"

class Renderer
{
public:
	bool IsInitialized() const noexcept;
	void Init(DeviceResources*) noexcept;
	void Shutdown() noexcept;
	void Render();
	DeviceResources* pDeviceResources = nullptr;
	Box* box = nullptr;
};

