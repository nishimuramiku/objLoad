#include "Device.h"
#include"Window.h"


Device::Device(const Window* window)
	:m_pDevice(nullptr),
	m_pSwapChain(nullptr),
	m_Window(nullptr),
	deviceContext(nullptr),
	m_pDSV(nullptr),
	m_pRTV(nullptr),
	m_pDSSRV(nullptr),
	m_pRTSRV(nullptr),
	m_pRTT(nullptr),
	m_pDST(nullptr),
	m_DriverType(D3D_DRIVER_TYPE_HARDWARE),
	m_FeatureLevel(D3D_FEATURE_LEVEL_11_0),
	createDeviceFlags(0)

{
	m_Window = window;
	m_Width = window->GetWidth();
	m_Height = window->GetHeight();

	m_ClearColor[0] = 1.0f;
	m_ClearColor[1] = 1.0f;
	m_ClearColor[2] = 1.0f;
	m_ClearColor[3] = 1.0f;

	deviceContext = new DeviceContext(m_Width, m_Height);

	ZeroMemory(&sd, sizeof(DXGI_SWAP_CHAIN_DESC));
	sd.BufferCount = m_Window->GetMultiSampleCount();
	sd.BufferDesc.Width = m_Width;
	sd.BufferDesc.Height = m_Height;
	sd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;
	sd.BufferDesc.RefreshRate.Numerator = 60;
	sd.BufferDesc.RefreshRate.Denominator = 1;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	sd.OutputWindow = m_Window->GethWnd();
	sd.SampleDesc.Count = m_Window->GetMultiSampleCount();
	sd.SampleDesc.Quality = m_Window->GetMultiSampleQuality();
	sd.Windowed = TRUE;


	ZeroMemory(&td, sizeof(D3D11_TEXTURE2D_DESC));
	td.Width = (UINT)m_Width;
	td.Height = (UINT)m_Height;
	td.MipLevels = 1;
	td.ArraySize = 1;
	td.SampleDesc.Count = m_Window->GetMultiSampleCount();
	td.SampleDesc.Quality = m_Window->GetMultiSampleQuality();
	td.Usage = D3D11_USAGE_DEFAULT;
	td.BindFlags = D3D11_BIND_DEPTH_STENCIL | D3D11_BIND_SHADER_RESOURCE;
	td.CPUAccessFlags = 0;
	td.MiscFlags = 0;


	ZeroMemory(&dsvd, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

	ZeroMemory(&srvd, sizeof(D3D11_SHADER_RESOURCE_VIEW_DESC));
}


Device::~Device()
{
	delete(deviceContext);

	if (m_pSwapChain)
	{
		m_pSwapChain->Release();
		m_pSwapChain = nullptr;

	}

	if (m_pDevice)
	{
		m_pDevice->Release();
		m_pDevice = nullptr;
	}

	if (m_pDSSRV)
	{
		m_pDSSRV->Release();
		m_pDSSRV = nullptr;
	}

	if (m_pDSV)
	{
		m_pDSV->Release();
		m_pDSV = nullptr;
	}

	if (m_pDST)
	{
		m_pDST->Release();
		m_pDST = nullptr;
	}

	if (m_pRTSRV)
	{
		m_pRTSRV->Release();
		m_pRTSRV = nullptr;
	}
	if (m_pRTV)
	{
		m_pRTV->Release();
		m_pRTV = nullptr;
	}
	if (m_pRTT)
	{
		m_pRTT->Release();
		m_pRTT = nullptr;
	}

}

bool Device::CreateSwapchain()
{

	D3D_FEATURE_LEVEL featureLevels[] =
	{
		D3D_FEATURE_LEVEL_11_0,
		D3D_FEATURE_LEVEL_10_1,
		D3D_FEATURE_LEVEL_10_0,
	};
	UINT numFeatureLevels = sizeof(featureLevels) / sizeof(featureLevels[0]);

	HRESULT hr = D3D11CreateDeviceAndSwapChain(
		nullptr,
		m_DriverType,
		nullptr,
		createDeviceFlags,
		featureLevels,
		numFeatureLevels,
		D3D11_SDK_VERSION,
		&sd,
		&m_pSwapChain,
		&m_pDevice,
		&m_FeatureLevel,
		&deviceContext->m_pDeviceContext);

	if (FAILED(hr))
	{
		return false;
	}
	if (!CreateDefaultRenderTarget())
	{
		return false;
	}
	if (!CreateDefaultDepthStencil())
	{
		return false;
	}

	return true;


}

bool Device::CreateDefaultRenderTarget()
{

	HRESULT hr = m_pSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*)&m_pRTT);
	if (FAILED(hr))
	{
		return false;
	}


	hr = m_pDevice->CreateRenderTargetView(m_pRTT, nullptr, &(m_pRTV));
	if (FAILED(hr))
	{
		return false;
	}

	hr = m_pDevice->CreateShaderResourceView(m_pRTT, nullptr, &(m_pRTSRV));
	if (FAILED(hr))
	{
		return false;
	}
	return true;
}


bool Device::CreateDefaultDepthStencil()
{
	DXGI_FORMAT textureFormat = m_Window->GetDepthStencilFormat();
	DXGI_FORMAT resourceFormat = m_Window->GetDepthStencilFormat();

	switchFormat(&textureFormat, &resourceFormat);

	td.Format = textureFormat;
	HRESULT hr = m_pDevice->CreateTexture2D(&td, NULL, &m_pDST);
	if (FAILED(hr))
	{
		return false;
	}

	dsvd.Format = m_Window->GetDepthStencilFormat();
	if (m_Window->GetMultiSampleCount() == 0)
	{
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
		dsvd.Texture2D.MipSlice = 0;
	}
	else
	{
		dsvd.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2DMS;
	}

	hr = m_pDevice->CreateDepthStencilView(m_pDST, &dsvd, &m_pDSV);
	if (FAILED(hr))
	{
		return false;
	}

	srvd.Format = resourceFormat;

	if (m_Window->GetMultiSampleCount() == 0)
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
		srvd.Texture2D.MostDetailedMip = 0;
		srvd.Texture2D.MipLevels = 1;

	}
	else
	{
		srvd.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DMS;
	}


	hr = m_pDevice->CreateShaderResourceView(m_pDST, &srvd, &m_pDSSRV);
	if (FAILED(hr))
	{
		return false;
	}

	return true;
}


void  Device::InitDeviceContext()
{
	deviceContext->InitDeviceContext(m_pRTV, m_pDSV);

}


void Device::Begin()

{
	deviceContext->m_pDeviceContext->ClearRenderTargetView(m_pRTV, m_ClearColor);
	deviceContext->m_pDeviceContext->ClearDepthStencilView(m_pDSV, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	deviceContext->m_pDeviceContext->OMSetRenderTargets(1, &m_pRTV, nullptr);

}

void Device::switchFormat(DXGI_FORMAT* textureFormat, DXGI_FORMAT* resourceFormat)
{
	switch (m_Window->GetDepthStencilFormat())
	{
	case DXGI_FORMAT_D16_UNORM:
	{
		*textureFormat = DXGI_FORMAT_R16_TYPELESS;
		*resourceFormat = DXGI_FORMAT_R16_UNORM;
	}break;

	case DXGI_FORMAT_D24_UNORM_S8_UINT:
	{
		*textureFormat = DXGI_FORMAT_R24G8_TYPELESS;
		*resourceFormat = DXGI_FORMAT_R24_UNORM_X8_TYPELESS;
	}break;

	case DXGI_FORMAT_D32_FLOAT:
	{
		*textureFormat = DXGI_FORMAT_R32_TYPELESS;
		*resourceFormat = DXGI_FORMAT_R32_FLOAT;
	}break;

	case DXGI_FORMAT_D32_FLOAT_S8X24_UINT:
	{
		*textureFormat = DXGI_FORMAT_R32G8X24_TYPELESS;
		*resourceFormat = DXGI_FORMAT_R32_FLOAT_X8X24_TYPELESS;
	}break;

	}
}