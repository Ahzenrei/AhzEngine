#pragma once

#include <wrl.h>
#include <d3d11.h>

template <class T>
class PrimitiveBase : Primitive
{
public:

protected:
	static Microsoft::WRL::ComPtr<ID3D11Buffer>            pVertexBuffer;
	static Microsoft::WRL::ComPtr<ID3D11Buffer>            pIndexBuffer;
	static Microsoft::WRL::ComPtr<ID3D11VertexShader>      pVertexShader;
	static Microsoft::WRL::ComPtr<ID3D11InputLayout>       pInputLayout;
	static Microsoft::WRL::ComPtr<ID3D11InputLayout>       pInputLayoutExtended;
	static Microsoft::WRL::ComPtr<ID3D11PixelShader>       pPixelShader;
	static Microsoft::WRL::ComPtr<ID3D11Buffer>            pConstantBuffer;
};

template <class T>
Microsoft::WRL::ComPtr<ID3D11Buffer>            PrimitiveBase<T>::pVertexBuffer;
template <class T>
Microsoft::WRL::ComPtr<ID3D11Buffer>            PrimitiveBase<T>::pIndexBuffer;
template <class T>
Microsoft::WRL::ComPtr<ID3D11VertexShader>      PrimitiveBase<T>::pVertexShader;
template <class T>
Microsoft::WRL::ComPtr<ID3D11InputLayout>       PrimitiveBase<T>::pInputLayout;
template <class T>
Microsoft::WRL::ComPtr<ID3D11InputLayout>       PrimitiveBase<T>::pInputLayoutExtended;
template <class T>
Microsoft::WRL::ComPtr<ID3D11PixelShader>       PrimitiveBase<T>::pPixelShader;
template <class T>
Microsoft::WRL::ComPtr<ID3D11Buffer>            PrimitiveBase<T>::pConstantBuffer;