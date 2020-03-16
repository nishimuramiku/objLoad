#pragma once
#include<d3d11.h>

class Sampler
{
public:
	Sampler();
	~Sampler();

	bool CreateSamplerState(ID3D11Device* m_pDevice);
	void SetSampler(ID3D11DeviceContext* m_DeviceContext);

private:
	D3D11_SAMPLER_DESC smpDesc;
	ID3D11SamplerState* m_pSampler;

};

