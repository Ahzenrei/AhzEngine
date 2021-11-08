#include "AssimpImport.h"
#include <assimp/Importer.hpp>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

SceneElement* AssimpImport::ImportFBX(const std::string& pFile, ID3D11Device* device) noexcept
{
	Assimp::Importer importer;

	// And have it read the given file with some example postprocessing
	// Usually - if speed is not the most important aspect for you - you'll
	// probably to request more postprocessing than we do in this example.
	const aiScene* scene = importer.ReadFile(pFile,
		aiProcess_Triangulate |
		aiProcess_JoinIdenticalVertices
	);

	if (!scene) return nullptr;

	if (!scene->HasMeshes()) nullptr;

	aiMesh* pMesh = scene->mMeshes[0];

	std::vector<Mesh::VertexData> meshVertices;
	meshVertices.reserve(pMesh->mNumVertices);

	for (unsigned int i = 0; i < pMesh->mNumVertices; i++)
	{
		meshVertices.push_back(
			{
				DirectX::XMFLOAT3(pMesh->mVertices[i].x, pMesh->mVertices[i].z, pMesh->mVertices[i].y),
				DirectX::XMFLOAT4(0.5,   0.3,   0.3, 1),
				DirectX::XMFLOAT2(1, 0),
				*reinterpret_cast<DirectX::XMFLOAT3*>(&pMesh->mNormals[i])
			});
	}

	std::vector<unsigned short> meshIndices;
	meshIndices.reserve((pMesh->mNumFaces * (size_t)3));
	for (unsigned int i = 0; i < pMesh->mNumFaces; i++)
	{
		const auto& face = pMesh->mFaces[i];
		assert(face.mNumIndices == 3);
		meshIndices.push_back(face.mIndices[0]);
		meshIndices.push_back(face.mIndices[1]);
		meshIndices.push_back(face.mIndices[2]);
	}

	Mesh* mesh = new Mesh(meshVertices, meshIndices);
	mesh->LoadDataToGPU(device);

	Shader* shader = new Shader(L"BoxVertexShader.cso", L"BoxPixelShader.cso", device);
	Material* mat = new Material(shader);

	MeshComponent* meshcomp = new MeshComponent(mesh, mat, device);

	SceneElement* element = new SceneElement();
	element->AddComponent(dynamic_cast<Component*>(meshcomp));

	return element;
}
