#pragma once
#include<d3d11.h>
#include<string>

class Window
{

public:
	struct Config
	{
		UINT swapChainCount;
		DXGI_FORMAT swapChainFormat;
		DXGI_FORMAT depthStencilFormat;
		UINT multiSampleCount;
		UINT multiSampleQuality;
		UINT width;
		UINT height;
		LPSTR title;

		Config()
			:swapChainCount(2),
			swapChainFormat(DXGI_FORMAT_D24_UNORM_S8_UINT),
			depthStencilFormat(DXGI_FORMAT_D24_UNORM_S8_UINT),
			multiSampleCount(4),
			multiSampleQuality(0),
			width(960),
			height(960),
			title((LPSTR)"tetrisApp")
		{}

	};

	Window(const Config& config);
	~Window();

	bool InitWnd();

	UINT GetWidth() const
	{
		return m_Width;
	}
	UINT GetHeight() const
	{
		return m_Height;
	}
	UINT GetMultiSampleCount() const
	{
		return m_MultiSampleCount;
	}
	UINT GetMultiSampleQuality() const
	{
		return m_MultiSampleQuality;
	}
	UINT GetSwapChainCount() const
	{
		return m_SwapChainCount;
	}
	HWND GethWnd() const
	{
		return m_hWnd;
	}
	DXGI_FORMAT GetSwapChainFormat() const
	{
		return m_SwapChainFormat;
	}
	DXGI_FORMAT GetDepthStencilFormat() const
	{
		return m_DepthStencilFormat;
	}


private:
	void TermWnd();
	static LRESULT CALLBACK WndProc(HWND hWnd, UINT nMsg, WPARAM wp, LPARAM lp);


private:
	HINSTANCE m_hInst;
	std::string m_Title;
	UINT m_Width;
	UINT m_Height;
	UINT m_MultiSampleCount;
	UINT m_MultiSampleQuality;
	UINT m_SwapChainCount;
	HWND m_hWnd;
	DXGI_FORMAT m_SwapChainFormat;
	DXGI_FORMAT m_DepthStencilFormat;

};
