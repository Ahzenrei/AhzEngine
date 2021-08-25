#include "Engine.h"

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

void Engine::init(HWND hWnd) noexcept
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

	//We create our Device, SwapChain and DeviceContext 
	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
#if NDEBUG
		0,
#else
		D3D11_CREATE_DEVICE_DEBUG,
#endif
		featureLevels,
		1,
		D3D11_SDK_VERSION,
		&sd,
		&pSwap,
		&pDevice,
		pFeatureLevel,
		&pContext
	);

	if (FAILED(hr))
		LogError(hr);

	hr = pSwap->GetBuffer(0,
						_uuidof(ID3D11Texture2D),
						(void**)&pSwapChainBuffer);

	if (FAILED(hr))
		LogError(hr);

#if !NDEBUG
	hr = pDevice->QueryInterface (__uuidof( ID3D11Debug), (void **)&pDebugger);

	if (FAILED(hr))
		LogError(hr);
#endif

	hr = pDevice->CreateRenderTargetView(pSwapChainBuffer, 0, &pView);

	if (FAILED(hr))
		LogError(hr);

	D3D11_TEXTURE2D_DESC desc;
	desc.Width = 640;
	desc.Height = 480;
	desc.MipLevels = 1;
	desc.ArraySize = 1;
	desc.Format = DXGI_FORMAT_D32_FLOAT;
	desc.SampleDesc.Count = 1;
	desc.SampleDesc.Quality = 0;
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;


	hr = pDevice->CreateTexture2D(&desc, 0, &pDepthBuffer);

	if (FAILED(hr))
		LogError(hr);

	hr = pDevice->CreateDepthStencilView(pDepthBuffer, 0, &pDepthView);

	if (FAILED(hr))
		LogError(hr);
}

void Engine::update() const
{


}
