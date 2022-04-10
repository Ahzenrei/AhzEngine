#include "Shader.h"
#include <assert.h> 
#include <iostream>
#include <vector>


Shader::Shader(const wchar_t* vertexShaderPath, const wchar_t* pixelShaderPath, ID3D11Device* device) 
{
	assert(vertexShaderPath != nullptr && pixelShaderPath != nullptr && device != nullptr);

	HRESULT hr = S_OK;

	ID3DBlob* pBlobByte;

	D3DReadFileToBlob(vertexShaderPath, &pBlobByte);
	hr = device->CreateVertexShader(
		pBlobByte->GetBufferPointer(),
		pBlobByte->GetBufferSize(),
		nullptr,
		&pVertexShader
	);

	D3D11_INPUT_ELEMENT_DESC iaDesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,
		0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "UV", 0, DXGI_FORMAT_R32G32_FLOAT,
		0, 28, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT,
		0, 36, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = device->CreateInputLayout(
		iaDesc,
		ARRAYSIZE(iaDesc),
		pBlobByte->GetBufferPointer(),
		pBlobByte->GetBufferSize(),
		&pInputLayout
	);

	D3DReadFileToBlob(pixelShaderPath, &pBlobByte);
	hr = device->CreatePixelShader(
		pBlobByte->GetBufferPointer(),
		pBlobByte->GetBufferSize(),
		nullptr,
		&pPixelShader
	);
}
