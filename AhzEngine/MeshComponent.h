#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshComponent : public Component
{
public:
	MeshComponent(Mesh * _mesh, Material * _mat, ID3D11Device* device) noexcept;
	~MeshComponent();

	ComponentType GetComponentType() const noexcept override;
	void UpdateModelMatrice(DirectX::XMMATRIX _model) noexcept;
	DirectX::XMFLOAT4X4 GetModelMatrice() noexcept;

	Mesh * pMesh;
	Material * pMat;

	DirectX::XMFLOAT4X4 model;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pModel;
};