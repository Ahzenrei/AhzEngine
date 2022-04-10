#include "Renderer.h"
#include "Box.h"
#include <DirectXMath.h>
#include <cmath>

void Renderer::Init(DeviceResources* _pDeviceResources) 
{
	pDeviceResources = _pDeviceResources;

	CreateViewAndPerspective();

	CD3D11_BUFFER_DESC iDesc(
		sizeof(Camera),
		D3D11_BIND_CONSTANT_BUFFER
	);

	D3D11_SUBRESOURCE_DATA iData;
	ZeroMemory(&iData, sizeof(D3D11_SUBRESOURCE_DATA));
	iData.pSysMem = &camera;
	iData.SysMemPitch = 0;
	iData.SysMemSlicePitch = 0;

	pDeviceResources->GetDevice()->CreateBuffer(
		&iDesc,
		&iData,
		&pCamera
	);

}

void Renderer::Shutdown() 
{
}

bool Renderer::IsInitialized() const 
{
	return pDeviceResources != nullptr;
}

void Renderer::Render() 
{
	// Use the Direct3D device context to draw.
	ID3D11DeviceContext* context = pDeviceResources->GetDeviceContext();
	ID3D11RenderTargetView* renderTarget = pDeviceResources->GetRenderTarget();
	ID3D11DepthStencilView* depthStencil = pDeviceResources->GetDepthStencil();

	context->UpdateSubresource(
		pCamera.Get(),
		0,
		nullptr,
		&camera,
		0,
		0
	);

	// Clear the render target and the z-buffer.
	const float teal[] = { 0.098f, 0.098f, 0.098f, 1.000f };
	context->ClearRenderTargetView(
		renderTarget,
		teal
	);

	context->ClearDepthStencilView(
		depthStencil,
		D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL,
		1.0f,
		0
	);

	// Set the render target.
	context->OMSetRenderTargets(
		1,
		&renderTarget,
		depthStencil
	);

	for (const auto& element : sceneElementsToDraw)
	{

		const MeshComponent * mesh = dynamic_cast<MeshComponent *>(element->GetComponent(Component::ComponentType::Mesh));

		if (mesh == nullptr) continue;

		context->UpdateSubresource(
			mesh->pModel.Get(),
			0,
			nullptr,
			&mesh->model,
			0,
			0
		);

		// Set up the IA stage by setting the input topology and layout.
		UINT stride = sizeof(Mesh::VertexData);
		UINT offset = 0;

		context->IASetVertexBuffers(
			0,
			1,
			mesh->pMesh->pVertexBuffer.GetAddressOf(),
			&stride,
			&offset
		);

		context->IASetIndexBuffer(
			mesh->pMesh->pIndexBuffer.Get(),
			DXGI_FORMAT_R32_UINT,
			0
		);

		context->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
		);

		context->IASetInputLayout(mesh->pMat->shader->pInputLayout.Get());

		// Set up the vertex shader stage.
		context->VSSetShader(
			mesh->pMat->shader->pVertexShader.Get(),
			nullptr,
			0
		);

		context->VSSetConstantBuffers(
			0,
			1,
			pCamera.GetAddressOf()
		);

		context->VSSetConstantBuffers(
			1,
			1,
			mesh->pModel.GetAddressOf()
		);

		// Set up the pixel shader stage.
		context->PSSetShader(
			mesh->pMat->shader->pPixelShader.Get(),
			nullptr,
			0
		);

		// Calling Draw tells Direct3D to start sending commands to the graphics device.
		context->DrawIndexed(
			(uint32_t)mesh->pMesh->indices.size(),
			0,
			0
		);
	}
}

void Renderer::CreateViewAndPerspective() 
{
	// Use DirectXMath to create view and perspective matrices.

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.25f, -3.5f, 0.f);
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 0.f);
	DirectX::XMVECTOR up = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.f);

	DirectX::XMStoreFloat4x4(
		&camera.view,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixLookAtRH(
				eye,
				at,
				up
			)
		)
	);

	float aspectRatioX = 4.f / 3.f;
	float aspectRatioY = 1;

	DirectX::XMStoreFloat4x4(
		&camera.projection,
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixPerspectiveFovRH(
				2.0f * std::atan(std::tan(DirectX::XMConvertToRadians(70) * 0.5f) / aspectRatioY),
				aspectRatioX,
				0.01f,
				100.0f
			)
		)
	);
}

void Renderer::UpdateCamera() 
{

}

void Renderer::AddElementToDraw(SceneElement* element) 
{
	assert(element != nullptr);

	sceneElementsToDraw.push_back(element);
}
