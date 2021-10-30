#include "MeshComponent.h"

MeshComponent::MeshComponent(Mesh * _mesh, Material * _mat) noexcept
	:	pMesh(_mesh), pMat(_mat)
{}
