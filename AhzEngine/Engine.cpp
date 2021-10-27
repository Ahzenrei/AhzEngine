#include "Engine.h"

Renderer Engine::renderer;

void Engine::init(HWND hWnd) noexcept
{
	renderer.init(hWnd);
}

void Engine::doFrame() noexcept
{
	
}
