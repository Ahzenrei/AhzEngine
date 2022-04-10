#pragma once
#include "SceneElement.h"
#include <string>

class AssimpImport
{
public:
	static SceneElement* ImportFBX(const std::string& pFile, ID3D11Device* device) ;
};

