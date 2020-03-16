#pragma once

#include<d3d11.h>

class VertexShader;
class PixelShader;
class Sampler;

class Material
{
public:
	Material();

	~Material();

	bool createMaterial(ID3D11Device* m_pDevice,
		ID3D11DeviceContext* m_pDeviceContext,
		const wchar_t* imageFileName,
		D3D_PRIMITIVE_TOPOLOGY topology,
		D3D11_RASTERIZER_DESC rd,
		const wchar_t* VSshaderFileName,
		LPCSTR VSentryPoint,
		const wchar_t* PSshaderFileName,
		LPCSTR PSentryPoint);

	void releaseMaterial();

private:


private:

	VertexShader* vs;
	PixelShader* ps;
	Sampler* samp;

	ID3D11Resource* m_pTexture;
	ID3D11ShaderResourceView* m_pTextureView;
	ID3D11RasterizerState* m_pRS;
};