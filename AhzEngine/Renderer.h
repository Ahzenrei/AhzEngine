#pragma once

#include "DeviceResources.h"

class Renderer
{
public:
	void init(HWND hWnd) noexcept;
private:
	static DeviceResources deviceResources;
};

