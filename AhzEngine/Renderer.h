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

	bool IsInitialized() const ;
	void Init(DeviceResources*) ;
	void Shutdown() ;
	void Render() ;
	void CreateViewAndPerspective() ;
	void UpdateCamera() ;
	void AddElementToDraw(SceneElement * element) ;

	DeviceResources* pDeviceResources = nullptr;

	std::vector<SceneElement*> sceneElementsToDraw;

	Camera camera;
	Microsoft::WRL::ComPtr<ID3D11Buffer> pCamera;
};