#include "MeshComponent.h"

MeshComponent::MeshComponent(Mesh& _mesh, Material& _mat) noexcept
	:	mesh(_mesh), mat(_mat)
{}
