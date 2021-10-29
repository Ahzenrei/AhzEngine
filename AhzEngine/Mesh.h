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
		DirectX::XMFLOAT3 color;
		DirectX::XMFLOAT3 uv;
		DirectX::XMFLOAT3 normal;
	};

	Mesh(std::unique_ptr<VertexData>, std::unique_ptr<std::vector<unsigned short>>) noexcept;

	HRESULT LoadDataToGPU(ID3D11Device *) noexcept;
	//void UnloadDataFromGPU() noexcept;

private:

	std::unique_ptr<VertexData> pVertices;
	std::unique_ptr<std::vector<unsigned short>> pIndices;
	bool dataLoaded = false;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		pVertexBuffer = nullptr;
	Microsoft::WRL::ComPtr<ID3D11Buffer>		pIndexBuffer = nullptr;
};

