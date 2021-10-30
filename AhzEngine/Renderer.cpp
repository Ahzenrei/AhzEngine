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

    meshes.push_back(meshcomp);
}

void Renderer::Shutdown() noexcept
{
    delete(meshes[0]->pMat->shader);
    delete(meshes[0]->pMat);
    delete(meshes[0]->pMesh);
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

    for (const auto& mesh : meshes)
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

        // Set up the pixel shader stage.
        context->PSSetShader(
            mesh->pMat->shader->pPixelShader.Get(),
            nullptr,
            0
        );

        // Calling Draw tells Direct3D to start sending commands to the graphics device.
        context->DrawIndexed(
            (UINT)mesh->pMesh->vertices.size(),
            0,
            0
        );
    }


}