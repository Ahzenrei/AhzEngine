#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshComponent : Component
{
public:
	MeshComponent(Mesh * _mesh, Material * _mat) noexcept;
	~MeshComponent() = default;

	inline ComponentType GetComponentType() const noexcept override;

	Mesh * pMesh;
	Material * pMat;
};