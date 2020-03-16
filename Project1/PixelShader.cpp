#include "PixelShader.h"
#include"ShaderUtil.h"



PixelShader::PixelShader()
	:pPSBlob(nullptr),
	m_pPS(nullptr)
{
}


PixelShader::~PixelShader()
{
	pPSBlob->Release();
	m_pPS->Release();
}

bool PixelShader::compileShader(const wchar_t* m_shaderFileName, LPCSTR entryPoint)
{
	HRESULT hr = CompileShaderFromFile((WCHAR*)m_shaderFileName, entryPoint, "ps_5_0", &pPSBlob);
	if (FAILED(hr))
	{
		return false;
	}
	return true;

}

bool PixelShader::createShader(ID3D11Device* m_pDevice)
{
	HRESULT hr = m_pDevice->CreatePixelShader(
		pPSBlob->GetBufferPointer(),
		pPSBlob->GetBufferSize(),
		nullptr,
		&m_pPS);

	if (FAILED(hr))
	{
		return false;
	}
	return true;
}

void PixelShader::setShader(ID3D11DeviceContext* m_pDeviceContext)
{
	m_pDeviceContext->PSSetShader(m_pPS, NULL, 0);
}