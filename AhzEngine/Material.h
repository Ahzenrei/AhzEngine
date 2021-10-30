#pragma once

#include <wrl.h>
#include <d3d11.h>
#include <DirectXMath.h>
#include "Shader.h"

class Material
{
public:
	Material() = delete;
	Material(Shader*) noexcept;
	Shader* shader = nullptr;
};