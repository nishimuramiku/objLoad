#pragma once
#include<d3d11.h>

class PixelShader
{
public:
	PixelShader();
	~PixelShader();

	bool compileShader(const wchar_t* m_shaderFileName, LPCSTR entryPoint);
	bool createShader(ID3D11Device* m_pDevice);
	void setShader(ID3D11DeviceContext* m_pDeviceContext);

private:
	ID3DBlob* pPSBlob;
	ID3D11PixelShader*  m_pPS;
};
