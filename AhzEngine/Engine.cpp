#include "Engine.h"

Renderer Engine::renderer;

void Engine::init(HWND hWnd) noexcept
{
	renderer.init(hWnd);
}

void Engine::doFrame() noexcept
{
	updateCamera();

	updateSceneElements();

	renderScene();

	swapBuffers();
}

void Engine::updateCamera() noexcept
{
}

void Engine::updateSceneElements() noexcept
{
}

void Engine::renderScene() noexcept
{
}

void Engine::swapBuffers() noexcept
{
}
