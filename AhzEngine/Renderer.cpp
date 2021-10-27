#include "Renderer.h"

DeviceResources Renderer::deviceResources;

void Renderer::init(HWND hWnd) noexcept
{
	deviceResources.init(hWnd);
}
