#pragma once

#include <wrl.h>
#include <d3d11.h>

class Material
{
public:

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>      pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>       pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       pPixelShader;
};