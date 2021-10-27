#pragma once
#include <d3d11.h>

class Renderer
{
public:
	void init(HWND hWnd) noexcept;

private:
	ID3D11Device* pDevice = nullptr;
	ID3D11DeviceContext* pContext = nullptr;

	IDXGISwapChain* pSwap = nullptr;
	ID3D11Texture2D* pSwapChainBuffer = nullptr;

	ID3D11RenderTargetView* pView = nullptr;

	ID3D11Texture2D* pDepthBuffer = nullptr;
	ID3D11DepthStencilView* pDepthView = nullptr;
#if !NDEBUG
	ID3D11Debug* pDebugger = nullptr;
#endif
};

