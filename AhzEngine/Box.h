#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "d3dcompiler.h"
#include "Mesh.h"
#include "Material.h"

class Box
{
public:
	struct VertexData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 color;
	};

	Box() = delete;
	Box(ID3D11Device* device);

	void CreateShaders(ID3D11Device* device);
	void CreateMesh(ID3D11Device* device);
	void CreateViewAndPerspective(ID3D11Device* device);
	void Update();

	Material::ConstantBufferStruct constantBufferData;
	int indexCount;
	int frameCount;

	Microsoft::WRL::ComPtr<ID3D11Buffer>            pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>            pIndexBuffer;
	Microsoft::WRL::ComPtr<ID3D11VertexShader>      pVertexShader;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>       pInputLayout;
	Microsoft::WRL::ComPtr<ID3D11InputLayout>       pInputLayoutExtended;
	Microsoft::WRL::ComPtr<ID3D11PixelShader>       pPixelShader;
	Microsoft::WRL::ComPtr<ID3D11Buffer>            pConstantBuffer;


};
