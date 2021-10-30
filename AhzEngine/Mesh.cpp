#include "Mesh.h"

Mesh::Mesh(std::vector<VertexData> _vertices, std::vector<unsigned short> _indices) noexcept
{
	vertices = _vertices;
	indices = _indices;
}

HRESULT Mesh::LoadDataToGPU(ID3D11Device* device) noexcept
{
	HRESULT hr = S_OK;

	// Create vertex buffer:

	CD3D11_BUFFER_DESC vDesc(
		(UINT)vertices.size() * sizeof(Mesh::VertexData),
		D3D11_BIND_VERTEX_BUFFER
	);

	D3D11_SUBRESOURCE_DATA vData;
	ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
	vData.pSysMem = vertices.data();
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(
		&vDesc,
		&vData,
		&pVertexBuffer
	);

	CD3D11_BUFFER_DESC iDesc(
		(UINT)indices.size()* sizeof(unsigned short),
		D3D11_BIND_INDEX_BUFFER
	);

	D3D11_SUBRESOURCE_DATA iData;
	ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
	iData.pSysMem = indices.data();
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(
		&iDesc,
		&iData,
		&pIndexBuffer
	);

	dataLoaded = true;

	return hr;
}
