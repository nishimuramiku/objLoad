#include "Sampler.h"



Sampler::Sampler()
	:m_pSampler(nullptr)
{
	ZeroMemory(&smpDesc, sizeof(D3D11_SAMPLER_DESC));
	smpDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	smpDesc.AddressU = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressV = D3D11_TEXTURE_ADDRESS_CLAMP;
	smpDesc.AddressW = D3D11_TEXTURE_ADDRESS_CLAMP;
}


Sampler::~Sampler()
{
	m_pSampler->Release();
}

bool Sampler::CreateSamplerState(ID3D11Device* m_pDevice)
{
	HRESULT hr = m_pDevice->CreateSamplerState(&smpDesc, &m_pSampler);
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void Sampler::SetSampler(ID3D11DeviceContext* m_pDeviceContext)
{
	m_pDeviceContext->PSSetSamplers(0, 1, &m_pSampler);
}