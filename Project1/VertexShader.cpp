#include "VertexShader.h"
#include"ShaderUtil.h"



VertexShader::VertexShader()
	:m_pVS(nullptr),
	pVSBlob(nullptr),
	m_pIL(nullptr)
{
}


VertexShader::~VertexShader()
{
	m_pVS->Release();
	pVSBlob->Release();
	m_pIL->Release();
}

bool VertexShader::compileShader(const wchar_t* m_shaderFileName, LPCSTR entryPoint)
{
	HRESULT hr = CompileShaderFromFile((WCHAR*)m_shaderFileName, entryPoint, "vs_5_0", &pVSBlob);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}

bool VertexShader::createShader(ID3D11Device* m_pDevice)
{

	HRESULT hr = m_pDevice->CreateVertexShader(pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), NULL, &m_pVS);
	if (FAILED(hr))
	{
		return false;
	}
}

void VertexShader::setShader(ID3D11DeviceContext* m_pDeviceContext)
{
	m_pDeviceContext->VSSetShader(m_pVS, NULL, 0);
}

bool VertexShader::createInputLayout(ID3D11Device* m_pDevice)
{

	D3D11_INPUT_ELEMENT_DESC layout[] = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT,0,D3D11_APPEND_ALIGNED_ELEMENT,D3D11_INPUT_PER_VERTEX_DATA,0}
	};
	UINT numElements = sizeof(layout) / sizeof(layout[0]);

	HRESULT hr = m_pDevice->CreateInputLayout(layout, numElements, pVSBlob->GetBufferPointer(), pVSBlob->GetBufferSize(), &m_pIL);
	if (FAILED(hr))
	{
		return false;
	}
}

void VertexShader::setInputLayout(ID3D11DeviceContext* m_pDeviceContext)
{
	m_pDeviceContext->IASetInputLayout(m_pIL);
}