#include "MeshComponent.h"

MeshComponent::MeshComponent(Mesh * _mesh, Material * _mat) noexcept
	:	pMesh(_mesh), pMat(_mat)
{}

Component::ComponentType MeshComponent::GetComponentType() const noexcept
{
	return Component::ComponentType::Mesh;
}
