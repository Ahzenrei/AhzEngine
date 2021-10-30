#include "Engine.h"

Renderer Engine::renderer;
DeviceResources Engine::deviceResources;

void Engine::Init(HWND hWnd) noexcept
{
	deviceResources.Init(hWnd);
	renderer.Init(&deviceResources);
}

void Engine::Shutdown() noexcept
{
	renderer.Shutdown();
	deviceResources.Shutdown();
}

void Engine::DoFrame() noexcept
{
	UpdateCamera();

	UpdateSceneElements();

	RenderScene();

	SwapBuffers();
}

void Engine::UpdateCamera() noexcept
{
	renderer.UpdateCamera();
}

void Engine::UpdateSceneElements() noexcept
{
	//renderer.box->Update();
}

void Engine::RenderScene() noexcept
{
	renderer.Render();
}

void Engine::SwapBuffers() noexcept
{
	deviceResources.PresentBackBuffer();
}
