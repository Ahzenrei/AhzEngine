#pragma once
#include "Renderer.h"

class Engine
{
public:
	void init(HWND hWnd) noexcept;
	void doFrame() noexcept;
private:
	void updateCamera() noexcept;
	void updateSceneElements() noexcept;
	void renderScene() noexcept;
	void swapBuffers() noexcept;

	static Renderer renderer;
};