#pragma once

#include<d3d11_1.h>
#pragma comment(lib, "dxguid.lib")

class Window;
class Scene;

class Device
{
public:
	Device(const Window* window);
	~Device();

	void InitDeviceContext();
	void Begin();
	bool CreateSwapchain();

	void GetDevice(ID3D11Device** temp) const
	{
		*temp = m_pDevice;
	}
	void GetDeviceContext(ID3D11DeviceContext** temp) const
	{
		deviceContext->GetDeviceContext(*&temp);
	}
	void GetSwapChain(IDXGISwapChain** temp) const
	{
		*temp = m_pSwapChain;
	};
	void SetDevice(ID3D11Device* temp)
	{
		m_pDevice = temp;
	}
	void SetDeviceContext(ID3D11DeviceContext* temp)
	{
		deviceContext->SetDeviceContext(temp);
	}



private:
	bool CreateDefaultRenderTarget();
	bool CreateDefaultDepthStencil();
	void switchFormat(DXGI_FORMAT* textureFormat, DXGI_FORMAT* resourceFormat);

	class DeviceContext
	{
	public:
		DeviceContext(FLOAT m_Width, FLOAT m_Height);
		~DeviceContext();
		ID3D11DeviceContext* m_pDeviceContext;
		void InitDeviceContext(ID3D11RenderTargetView* m_pRTV, ID3D11DepthStencilView* m_pDSV);
		void GetDeviceContext(ID3D11DeviceContext** temp) const
		{
			*temp = m_pDeviceContext;

		}
		void SetDeviceContext(ID3D11DeviceContext* temp)
		{
			m_pDeviceContext = temp;
		};

	private:
		D3D11_VIEWPORT vp;
	};


private:

	const Window* m_Window;
	DeviceContext* deviceContext;

	ID3D11Device* m_pDevice;
	IDXGISwapChain* m_pSwapChain;

	ID3D11DepthStencilView* m_pDSV;
	ID3D11RenderTargetView* m_pRTV;
	ID3D11ShaderResourceView* m_pDSSRV;
	ID3D11ShaderResourceView* m_pRTSRV;
	ID3D11Texture2D* m_pRTT;
	ID3D11Texture2D* m_pDST;


	D3D_DRIVER_TYPE m_DriverType;
	D3D_FEATURE_LEVEL m_FeatureLevel;
	UINT createDeviceFlags;

	FLOAT m_ClearColor[4];
	FLOAT m_Width;
	FLOAT m_Height;

	DXGI_SWAP_CHAIN_DESC sd;
	D3D11_TEXTURE2D_DESC td;
	D3D11_DEPTH_STENCIL_VIEW_DESC dsvd;
	D3D11_SHADER_RESOURCE_VIEW_DESC srvd;
};