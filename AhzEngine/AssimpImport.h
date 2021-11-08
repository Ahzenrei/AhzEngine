#pragma once
#include "SceneElement.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <string>

class AssimpImport
{
public:
	static SceneElement* ImportFBX(const std::string& pFile, ID3D11Device* device) noexcept;
};

