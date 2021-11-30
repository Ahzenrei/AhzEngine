#include "Engine.h"
#include "AssimpImport.h"
#include "Profiler.h"

Renderer Engine::renderer;
DeviceResources Engine::deviceResources;

void Engine::Init(HWND hWnd) noexcept
{
	deviceResources.Init(hWnd);
	renderer.Init(&deviceResources);

	cube = AssimpImport::ImportFBX("SuzanneUltra.fbx", deviceResources.GetDevice());

	renderer.AddElementToDraw(cube);
}

void Engine::Shutdown() noexcept
{
	renderer.Shutdown();
	deviceResources.Shutdown();

	auto mesh = dynamic_cast<MeshComponent*>(cube->GetComponent(Component::ComponentType::Mesh));
	delete(mesh->pMat->shader);
	delete(mesh->pMat);
	delete(mesh->pMesh);
	delete(mesh);
	delete(cube);
}

void Engine::DoFrame() noexcept
{
	UpdateCamera();

	UpdateSceneElements();

	{
		Profiler p("Render");
		RenderScene();
	}


	SwapBuffers();
}

void Engine::UpdateCamera() noexcept
{
	renderer.UpdateCamera();
}

void Engine::UpdateSceneElements() noexcept
{
	// Rotate the cube 1 degree per frame.
	auto mesh = dynamic_cast<MeshComponent*>(cube->GetComponent(Component::ComponentType::Mesh));
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
