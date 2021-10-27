#include "Renderer.h"
#include "Box.h"

DeviceResources Renderer::deviceResources;

void Renderer::init(HWND hWnd) noexcept
{
	deviceResources.init(hWnd);

	Box * b = new Box();
}
