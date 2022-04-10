#include "Material.h"

Material::Material(Shader* _shader) 
{
	assert(_shader != nullptr);
	shader = _shader;
}
