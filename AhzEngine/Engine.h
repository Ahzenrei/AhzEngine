#pragma once
#include "Renderer.h"

class Engine
{
public:
	void init(HWND hWnd) noexcept;
	void doFrame() noexcept;
private:
	static Renderer renderer;
};