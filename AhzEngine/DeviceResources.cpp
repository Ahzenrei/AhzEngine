#include "DeviceResources.h"

//Dirty Log
void LogError(HRESULT hr)
{
	LPTSTR error_text = NULL;
	FormatMessage(FORMAT_MESSAGE_FROM_SYSTEM |
		FORMAT_MESSAGE_ALLOCATE_BUFFER |
		FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL,
		hr,
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT),
		(LPTSTR)&error_text, 0,
		NULL);
	OutputDebugString(error_text);
	PostQuitMessage(-1);
}

void DeviceResources::init(HWND hWnd) noexcept
{
	//Swap chain description
	DXGI_SWAP_CHAIN_DESC sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.BufferDesc.Width = 640;
	sd.BufferDesc.Height = 480;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 2;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	sd.Flags = 0;

	//Features we want
	const D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_1,
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
		D3D_FEATURE_LEVEL_9_3,
		D3D_FEATURE_LEVEL_9_2,
		D3D_FEATURE_LEVEL_9_1
	};

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	//We create our Device, SwapChain and DeviceContext 
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		nullptr,
		&pContext
	);

	if (FAILED(hr))
		LogError(hr);

	//Retrieve back buffer from ths SwapChain
	hr = pSwap->GetBuffer(
		0,
		_uuidof(ID3D11Texture2D),
		(void**) &pBackBuffer);

	if (FAILED(hr))
		LogError(hr);

	//We create our render target view
	hr = pDevice->CreateRenderTargetView(
		pBackBuffer.Get(),
		nullptr, 
		&pRenderTarget
	);

	if (FAILED(hr))
		LogError(hr);

	//Retrieve back buffer description
	pBackBuffer->GetDesc(&backBufferDesc);

#if !NDEBUG
	hr = pDevice->QueryInterface(__uuidof(ID3D11Debug), (void**)&pDebugger);

	if (FAILED(hr))
		LogError(hr);
#endif

	//Create Depth Stencil buffer description
	D3D11_TEXTURE2D_DESC desc;
	desc.Width = backBufferDesc.Width;
	desc.Height = backBufferDesc.Height;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;

	//Create depth stencil buffer
	hr = pDevice->CreateTexture2D(
		&desc, 
		nullptr, 
		&pDepthStencil
	);

	if (FAILED(hr))
		LogError(hr);

	//Create depth stencil view
	hr = pDevice->CreateDepthStencilView(
		pDepthStencil.Get(), 
		nullptr, 
		&pDepthStencilView
	);

	if (FAILED(hr))
		LogError(hr);
	
	//Set viewport
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.Height = (float)backBufferDesc.Height;
	viewport.Width = (float)backBufferDesc.Width;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	pContext->RSSetViewports(
		1,
		&viewport
	);
}