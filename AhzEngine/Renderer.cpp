#include "Renderer.h"
#include "Box.h"
#include <DirectXMath.h>
#include <cmath>


void Renderer::Init(DeviceResources* _pDeviceResources) noexcept
{
    pDeviceResources = _pDeviceResources;
    box = new Box(pDeviceResources->GetDevice());
}

void Renderer::Shutdown() noexcept
{
    delete(box);
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
        box->pConstantBuffer.Get(),
        0,
        nullptr,
        &box->constantBufferData,
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

    // Set up the IA stage by setting the input topology and layout.
    UINT stride = sizeof(Box::VertexPositionColor);
    UINT offset = 0;

    context->IASetVertexBuffers(
        0,
        1,
        box->pVertexBuffer.GetAddressOf(),
        &stride,
        &offset
    );

    context->IASetIndexBuffer(
        box->pIndexBuffer.Get(),
        DXGI_FORMAT_R16_UINT,
        0
    );

    context->IASetPrimitiveTopology(
        D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST
    );

    context->IASetInputLayout(box->pInputLayout.Get());

    // Set up the vertex shader stage.
    context->VSSetShader(
        box->pVertexShader.Get(),
        nullptr,
        0
    );

    context->VSSetConstantBuffers(
        0,
        1,
        box->pConstantBuffer.GetAddressOf()
    );

    // Set up the pixel shader stage.
    context->PSSetShader(
        box->pPixelShader.Get(),
        nullptr,
        0
    );

    // Calling Draw tells Direct3D to start sending commands to the graphics device.
    context->DrawIndexed(
        box->indexCount,
        0,
        0
    );
}