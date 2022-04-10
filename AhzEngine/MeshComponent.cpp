#include "MeshComponent.h"

MeshComponent::MeshComponent(Mesh * _mesh, Material * _mat, ID3D11Device* device) 
	:	pMesh(_mesh), pMat(_mat)
{
	DirectX::XMStoreFloat4x4(&model, DirectX::XMMatrixIdentity());

	CD3D11_BUFFER_DESC iDesc(
		sizeof(DirectX::XMFLOAT4X4),
		D3D11_BIND_CONSTANT_BUFFER
	);

	D3D11_SUBRESOURCE_DATA iData;
	ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
	iData.pSysMem = &model;
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;

	device->CreateBuffer(
		&iDesc,
		&iData,
		&pModel
	);
}

MeshComponent::~MeshComponent()
{
}

Component::ComponentType MeshComponent::GetComponentType() const 
{
	return Component::ComponentType::Mesh;
}

void MeshComponent::UpdateModelMatrice(DirectX::XMMATRIX _model) 
{
	DirectX::XMStoreFloat4x4(&model, _model);
}

DirectX::XMFLOAT4X4 MeshComponent::GetModelMatrice() 
{
	return model;
}