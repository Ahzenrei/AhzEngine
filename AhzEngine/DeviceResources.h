#pragma once

#include <d3d11.h>
#include <wrl.h>

class DeviceResources
{
public:

	void Init(HWND hWnd) ;
	void Shutdown() ;
	ID3D11Device* GetDevice() ;
	ID3D11DeviceContext* GetDeviceContext() ;
	IDXGISwapChain* GetSwapChain() ;
	ID3D11RenderTargetView* GetRenderTarget() ;
	ID3D11DepthStencilView* GetDepthStencil() ;

	float GetAspectRatio() ;
	void PresentBackBuffer() ;


private:
	Microsoft::WRL::ComPtr<ID3D11Device>			pDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext>		pContext;
	Microsoft::WRL::ComPtr<IDXGISwapChain>			pSwap;

	Microsoft::WRL::ComPtr<ID3D11Texture2D>			pBackBuffer;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	pRenderTarget;

	Microsoft::WRL::ComPtr<ID3D11Texture2D>			pDepthStencil;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	pDepthStencilView;

#if !NDEBUG
	Microsoft::WRL::ComPtr<ID3D11Debug>				pDebugger;
#endif

	D3D_FEATURE_LEVEL       featureLevel;
	D3D11_TEXTURE2D_DESC    backBufferDesc;
	D3D11_VIEWPORT          viewport;
};

