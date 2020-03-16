#include "Material.h"
#include "WICTextureLoader.h"
#include "VertexShader.h"
#include "PixelShader.h"
#include "Sampler.h"


Material::Material()

	:m_pRS(nullptr),
	m_pTexture(nullptr),
	m_pTextureView(nullptr),
	vs(nullptr),
	ps(nullptr),
	samp(nullptr)
{

}


Material::~Material()
{
	
	m_pRS->Release();
	m_pTexture->Release();
	m_pTextureView->Release();

}
bool Material::createMaterial(
	ID3D11Device* m_pDevice,
	ID3D11DeviceContext* m_pDeviceContext,
	const wchar_t* imageFileName,
	D3D_PRIMITIVE_TOPOLOGY topology,
	D3D11_RASTERIZER_DESC rd,
	const wchar_t* VSshaderFileName,
	LPCSTR VSentryPoint,
	const wchar_t* PSshaderFileName,
	LPCSTR PSentryPoint)
{
	vs = new VertexShader();
	vs->compileShader(VSshaderFileName, VSentryPoint);
	vs->createShader(m_pDevice);
	vs->setShader(m_pDeviceContext);
	vs->createInputLayout(m_pDevice);
	vs->setInputLayout(m_pDeviceContext);

	HRESULT hr = DirectX::CreateWICTextureFromFile(m_pDevice, imageFileName, &m_pTexture, &m_pTextureView);
	if (FAILED(hr))
	{
		return false;
	}
	m_pDeviceContext->PSSetShaderResources(0, 1, &m_pTextureView);

	ps = new PixelShader();
	ps->compileShader(PSshaderFileName, PSentryPoint);
	ps->createShader(m_pDevice);
	ps->setShader(m_pDeviceContext);

	samp = new Sampler();
	samp->CreateSamplerState(m_pDevice);
	samp->SetSampler(m_pDeviceContext);

	m_pDeviceContext->IASetPrimitiveTopology(topology);
	if (FAILED(m_pDevice->CreateRasterizerState(&rd, &m_pRS)))
	{
		return false;
	}
	m_pDeviceContext->RSSetState(m_pRS);

	return true;
}

void Material::releaseMaterial()
{
	if (vs) {
		delete(vs);
		vs = nullptr;
	}
	if (ps) {
		delete(ps);
		ps = nullptr;
	}
	if (samp) {
		delete(samp);
		samp = nullptr;
	}
	m_pTextureView->Release();
	m_pTextureView = nullptr;

	m_pTexture->Release();
	m_pTexture = nullptr;

	m_pRS->Release();
	m_pRS = nullptr;

}