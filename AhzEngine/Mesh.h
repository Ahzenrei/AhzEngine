#pragma once

#include <wrl.h>
#include <d3d11.h>

class Mesh
{
public:

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer>	pVertexBuffer;
	Microsoft::WRL::ComPtr<ID3D11Buffer>    pIndexBuffer;
};

