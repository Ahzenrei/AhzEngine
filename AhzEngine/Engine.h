#pragma once
#include "Renderer.h"
#include "DeviceResources.h"

class Engine
{
public:
	void Init(HWND hWnd) noexcept;
	void Shutdown() noexcept;
	void DoFrame() noexcept;
private:
	void UpdateCamera() noexcept;
	void UpdateSceneElements() noexcept;
	void RenderScene() noexcept;
	void SwapBuffers() noexcept;

	//Here until I make an appropriate class
	SceneElement* cube;

	std::vector<SceneElement> sceneElements;

	int frameCount = 0;

	static Renderer renderer;
	static DeviceResources deviceResources;
};