#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>

class Material
{
public:
	struct ConstantBufferStruct {
		DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

private:
	Microsoft::WRL::ComPtr<ID3D11VertexShader>      pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       pPixelShader;
};