#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <d3dcompiler.h>
#include <memory>

class Shader
{
public:
	Shader() = delete;
	Shader(char* vertexShaderPath, char* pixelShaderPath) noexcept;

	HRESULT LoadShadersToGPU(ID3D11Device*) noexcept;

private:
	std::unique_ptr<BYTE> vsBytes;
	size_t vsBytesRead = 0;
	std::unique_ptr<BYTE> psBytes;
	size_t psBytesRead = 0;

	Microsoft::WRL::ComPtr<ID3D11VertexShader>      pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       pPixelShader;
};

