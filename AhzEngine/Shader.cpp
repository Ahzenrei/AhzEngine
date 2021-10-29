#include "Shader.h"
#include <assert.h> 
#include <iostream>


Shader::Shader(char * vertexShaderPath, char * pixelShaderPath) noexcept
{
	assert(vertexShaderPath != nullptr && pixelShaderPath != nullptr);

	FILE* vertexShader;
	FILE* pixelShader;

	size_t destSize = 4096;
	size_t bytesRead = 0;

	fopen_s(&vertexShader, vertexShaderPath, "rb");
	assert(vertexShader != nullptr);
	bytesRead = fread_s(vsBytes.get(), destSize, 1, 4096, vertexShader);

	fopen_s(&pixelShader, pixelShaderPath, "rb");
	assert(pixelShader != nullptr);
	bytesRead = fread_s(psBytes.get(), destSize, 1, 4096, pixelShader);

	fclose(pixelShader);
	fclose(vertexShader);
}

HRESULT Shader::LoadShadersToGPU(ID3D11Device* device) noexcept
{
	HRESULT hr = S_OK;

	hr = device->CreateVertexShader(
		vsBytes.get(),
		vsBytesRead,
		nullptr,
		&pVertexShader
	);

	hr = device->CreatePixelShader(
		psBytes.get(),
		psBytesRead,
		nullptr,
		&pPixelShader
	);

	return hr;
}
