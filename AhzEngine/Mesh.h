#pragma once

#include <vector>
#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include <memory>

class Mesh
{
public:
	struct VertexData
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT4 color;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT3 normal;
	};

	Mesh(std::vector<VertexData>, std::vector<unsigned short>) noexcept;

	HRESULT LoadDataToGPU(ID3D11Device *) noexcept;
	//void UnloadDataFromGPU() noexcept;



	std::vector<VertexData> vertices;
	std::vector<unsigned short> indices;
	bool dataLoaded = false;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		pVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		pIndexBuffer = nullptr;
};

