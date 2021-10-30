#include "Material.h"

Material::Material(Shader* _shader) noexcept
{
	assert(_shader != nullptr);
	shader = _shader;
}
