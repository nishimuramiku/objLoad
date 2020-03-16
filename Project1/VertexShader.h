#pragma once
#include<d3d11.h>

class VertexShader
{
public:
	VertexShader();
	~VertexShader();

	bool compileShader(const wchar_t* m_shaderFileName, LPCSTR entryPoint);
	bool createShader(ID3D11Device* m_pDevice);
	void setShader(ID3D11DeviceContext* m_pDeviceContext);
	bool createInputLayout(ID3D11Device* m_pDevice);
	void setInputLayout(ID3D11DeviceContext* m_pDeviceContext);

private:
	ID3D11VertexShader* m_pVS;
	ID3DBlob* pVSBlob;
	ID3D11InputLayout* m_pIL;
};
