#pragma once

#include "Component.h"
#include "Mesh.h"
#include "Material.h"

class MeshComponent : Component
{
public:
	MeshComponent(Mesh * _mesh, Material * _mat) noexcept;
	~MeshComponent() = default;
	Mesh * pMesh;
	Material * pMat;
};

