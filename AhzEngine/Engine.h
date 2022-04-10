#pragma once
#include "Renderer.h"
#include "DeviceResources.h"

class Engine
{
public:
	void Init(HWND hWnd) ;
	void Shutdown() ;
	void DoFrame() ;
private:
	void UpdateCamera() ;
	void UpdateSceneElements() ;
	void RenderScene() ;
	void SwapBuffers() ;

	//Here until I make an appropriate class
	SceneElement* cube = nullptr;

	std::vector<SceneElement> sceneElements;

	int frameCount = 0;

	static Renderer renderer;
	static DeviceResources deviceResources;
};