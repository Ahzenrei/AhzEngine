#include "Engine.h"

Renderer Engine::renderer;
DeviceResources Engine::deviceResources;

void Engine::Init(HWND hWnd) noexcept
{
	deviceResources.Init(hWnd);
	renderer.Init(&deviceResources);

	Shader* shader = new Shader(L"BoxVertexShader.cso", L"BoxPixelShader.cso", deviceResources.GetDevice());
	Material* mat = new Material(shader);

	std::vector<Mesh::VertexData> CubeVertices =
	{
		{DirectX::XMFLOAT3(-0.5f,-0.5f,-0.5f), DirectX::XMFLOAT4(0,   0,   0, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
		{DirectX::XMFLOAT3(-0.5f,-0.5f, 0.5f), DirectX::XMFLOAT4(0,   0,   1, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f,-0.5f), DirectX::XMFLOAT4(0,   1,   0, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
		{DirectX::XMFLOAT3(-0.5f, 0.5f, 0.5f), DirectX::XMFLOAT4(0,   1,   1, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},

		{DirectX::XMFLOAT3(0.5f,-0.5f,-0.5f), DirectX::XMFLOAT4(1,   0,   0, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
		{DirectX::XMFLOAT3(0.5f,-0.5f, 0.5f), DirectX::XMFLOAT4(1,   0,   1, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
		{DirectX::XMFLOAT3(0.5f, 0.5f,-0.5f), DirectX::XMFLOAT4(1,   1,   0, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
		{DirectX::XMFLOAT3(0.5f, 0.5f, 0.5f), DirectX::XMFLOAT4(1,   1,   1, 1), DirectX::XMFLOAT2(1, 0), DirectX::XMFLOAT3(0, 0, 0)},
	};

	// Create index buffer:
	std::vector<unsigned short> CubeIndices =
	{
		0,2,1, // -x
		1,2,3,

		4,5,6, // +x
		5,7,6,

		0,1,5, // -y
		0,5,4,

		2,6,7, // +y
		2,7,3,

		0,4,6, // -z
		0,6,2,

		1,3,7, // +z
		1,7,5,
	};

	Mesh* mesh = new Mesh(CubeVertices, CubeIndices);
	mesh->LoadDataToGPU(deviceResources.GetDevice());

	MeshComponent* meshcomp = new MeshComponent(mesh, mat, deviceResources.GetDevice());

	element = new SceneElement();
	element->AddComponent(dynamic_cast<Component*>(meshcomp));

	renderer.AddElementToDraw(element);
}

void Engine::Shutdown() noexcept
{
	renderer.Shutdown();
	deviceResources.Shutdown();

	auto mesh = dynamic_cast<MeshComponent*>(element->GetComponent(Component::ComponentType::Mesh));
	delete(mesh->pMat->shader);
	delete(mesh->pMat);
	delete(mesh->pMesh);
	delete(mesh);
	delete(element);
}

void Engine::DoFrame() noexcept
{
	UpdateCamera();

	UpdateSceneElements();

	RenderScene();

	SwapBuffers();
}

void Engine::UpdateCamera() noexcept
{
	renderer.UpdateCamera();
}

void Engine::UpdateSceneElements() noexcept
{
	// Rotate the cube 1 degree per frame.
	auto mesh = dynamic_cast<MeshComponent*>(element->GetComponent(Component::ComponentType::Mesh));
	mesh->UpdateModelMatrice(
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationY(
				DirectX::XMConvertToRadians(
					(float)frameCount++
				)
			)
		)
	);

	if (frameCount == MAXUINT)  frameCount = 0;
}

void Engine::RenderScene() noexcept
{
	renderer.Render();
}

void Engine::SwapBuffers() noexcept
{
	deviceResources.PresentBackBuffer();
}
