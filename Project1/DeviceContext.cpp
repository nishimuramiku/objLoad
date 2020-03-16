#include"Device.h"

Device::DeviceContext::DeviceContext(FLOAT m_Width, FLOAT m_Height)
{
	vp.Width = m_Width;
	vp.Height = m_Height;
	vp.MinDepth = 0.0f;
	vp.MaxDepth = 1.0f;
	vp.TopLeftX = 0;
	vp.TopLeftY = 0;
}


Device::DeviceContext::~DeviceContext()
{
}

void Device::DeviceContext::InitDeviceContext(ID3D11RenderTargetView* m_pRTV, ID3D11DepthStencilView* m_pDSV)
{
	m_pDeviceContext->OMSetRenderTargets(1, &m_pRTV, m_pDSV);
	m_pDeviceContext->RSSetViewports(1, &vp);
}
