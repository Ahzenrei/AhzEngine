#include "Mesh.h"

Mesh::Mesh(std::unique_ptr<VertexData> _vertices, std::unique_ptr<std::vector<unsigned short>> _indices) noexcept
{
	pVertices = std::move(_vertices);
	pIndices = std::move(_indices);
}

HRESULT Mesh::LoadDataToGPU(ID3D11Device* device) noexcept
{
	HRESULT hr = S_OK;

	// Create vertex buffer:

	CD3D11_BUFFER_DESC vDesc(
		sizeof(pVertices),
		D3D11_BIND_VERTEX_BUFFER
	);

	D3D11_SUBRESOURCE_DATA vData;
	ZeroMemory(&vData, sizeof(D3D11_SUBRESOURCE_DATA));
	vData.pSysMem = pVertices.get();
	vData.SysMemPitch = 0;
	vData.SysMemSlicePitch = 0;

	hr = device->CreateBuffer(
		&vDesc,
		&vData,
		&pVertexBuffer
	);

	CD3D11_BUFFER_DESC iDesc(
		(UINT)pIndices->size()* sizeof(unsigned short),
		D3D11_BIND_INDEX_BUFFER
	);

	D3D11_SUBRESOURCE_DATA iData;
	ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
	iData.pSysMem = pIndices->data();
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
