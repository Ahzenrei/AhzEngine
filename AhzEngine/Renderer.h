#pragma once
#include "DeviceResources.h"
#include "Box.h"
#include "MeshComponent.h"
#include <vector>
#include <DirectXMath.h>
#include "SceneElement.h"

class Renderer
{
public:

	struct Camera
	{
		//DirectX::XMFLOAT4X4 world;
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	bool IsInitialized() const noexcept;
	void Init(DeviceResources*) noexcept;
	void Shutdown() noexcept;
	void Render();
	void CreateViewAndPerspective();
	void UpdateCamera();

	DeviceResources* pDeviceResources = nullptr;

	std::vector<SceneElement*> sceneElementsToDraw;

	Camera camera;
	int frameCount = 0;
	Microsoft::WRL::ComPtr<ID3D11Buffer>	pCamera;
};

