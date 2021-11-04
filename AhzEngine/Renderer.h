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
		DirectX::XMFLOAT4X4 view;
		DirectX::XMFLOAT4X4 projection;
	};

	bool IsInitialized() const noexcept;
	void Init(DeviceResources*) noexcept;
	void Shutdown() noexcept;
	void Render() noexcept;
	void CreateViewAndPerspective() noexcept;
	void UpdateCamera() noexcept;
	void AddElementToDraw(SceneElement * element) noexcept;

	DeviceResources* pDeviceResources = nullptr;

	std::vector<SceneElement*> sceneElementsToDraw;

	Camera camera;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pCamera;
};