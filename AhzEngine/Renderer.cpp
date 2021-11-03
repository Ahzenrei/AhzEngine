#include "Renderer.h"
#include "Box.h"
#include <DirectXMath.h>
#include <cmath>

void Renderer::Init(DeviceResources* _pDeviceResources) noexcept
{
    pDeviceResources = _pDeviceResources;
    Shader * shader = new Shader(L"BoxVertexShader.cso", L"BoxPixelShader.cso", pDeviceResources->GetDevice());
    Material* mat = new Material(shader);

    //std::unique_ptr<VertexData>, std::unique_ptr<std::vector<unsigned short>>

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

    Mesh * mesh = new Mesh(CubeVertices, CubeIndices);
    mesh->LoadDataToGPU(pDeviceResources->GetDevice());
    MeshComponent* meshcomp = new MeshComponent(mesh, mat);

    sceneElementsToDraw.push_back(meshcomp);

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

void Renderer::Shutdown() noexcept
{
    delete(sceneElementsToDraw[0]->pMat->shader);
    delete(sceneElementsToDraw[0]->pMat);
    delete(sceneElementsToDraw[0]->pMesh);
}

bool Renderer::IsInitialized() const noexcept
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

    for (const auto& mesh : sceneElementsToDraw)
    {
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
            DXGI_FORMAT_R16_UINT,
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


        // Set up the pixel shader stage.
        context->PSSetShader(
            mesh->pMat->shader->pPixelShader.Get(),
            nullptr,
            0
        );

        // Calling Draw tells Direct3D to start sending commands to the graphics device.
        context->DrawIndexed(
            (UINT)mesh->pMesh->indices.size(),
            0,
            0
        );
    }


}

void Renderer::CreateViewAndPerspective()
{
	// Use DirectXMath to create view and perspective matrices.

	DirectX::XMVECTOR eye = DirectX::XMVectorSet(0.0f, 0.7f, 1.5f, 0.f);
	DirectX::XMVECTOR at = DirectX::XMVectorSet(0.0f, -0.1f, 0.0f, 0.f);
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

	float aspectRatioX = 4.f/3.f;
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
	//// Rotate the cube 1 degree per frame.
	//DirectX::XMStoreFloat4x4(
	//	&camera.world,
	//	DirectX::XMMatrixTranspose(
	//		DirectX::XMMatrixRotationY(
	//			DirectX::XMConvertToRadians(
	//				(float)frameCount++
	//			)
	//		)
	//	)
	//);

	//if (frameCount == MAXUINT)  frameCount = 0;
}