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
	Shader(const wchar_t* vertexShaderPath, const wchar_t* pixelShaderPath, ID3D11Device* device) noexcept;
	Shader& operator=(const Shader& source) = delete;
	Shader(const Shader&) = delete;
	Shader(Shader&&) = default;
	~Shader() = default;


	Microsoft::WRL::ComPtr<ID3D11VertexShader>      pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>		pInputLayout;
};

