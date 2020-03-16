#include "Window.h"



Window::Window(const Config& config)
	:m_hInst(NULL),
	m_hWnd(NULL),
	m_Width(config.width),
	m_Height(config.height),
	m_Title(config.title),
	m_MultiSampleCount(config.multiSampleCount),
	m_MultiSampleQuality(config.multiSampleQuality),
	m_SwapChainCount(config.swapChainCount),
	m_SwapChainFormat(config.swapChainFormat),
	m_DepthStencilFormat(config.depthStencilFormat)

{
}


Window::~Window()
{
	TermWnd();
}

bool Window::InitWnd()
{
	HINSTANCE hInst = GetModuleHandle(NULL);
	WNDCLASSEXA wc;

	wc.cbSize = sizeof(WNDCLASSEXA);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInst;
	wc.hIcon = LoadIcon(hInst, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = m_Title.c_str();
	wc.hIconSm = LoadIcon(hInst, IDI_APPLICATION);

	if (!RegisterClassExA(&wc))
	{
		return false;
	}

	m_hInst = hInst;

	RECT rc = { 0,0,m_Width, m_Height };
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);

	m_hWnd = CreateWindowA(
		m_Title.c_str(),
		m_Title.c_str(),
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		(rc.right - rc.left),
		(rc.bottom - rc.top),
		NULL,
		NULL,
		hInst,
		NULL);

	if (m_hWnd == NULL)
	{
		return false;
	}
	ShowWindow(m_hWnd, SW_SHOWNORMAL);

	return true;
}

void Window::TermWnd()
{
	if (m_hInst != NULL)
	{
		UnregisterClassA(m_Title.c_str(), m_hInst);
	}

	m_Title.clear();
}

LRESULT CALLBACK Window::WndProc(HWND hWnd, UINT uMsg, WPARAM wp, LPARAM lp)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (uMsg)
	{
	case WM_PAINT:
	{
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
	}break;

	case WM_DESTROY:
	{
		PostQuitMessage(0);
	}break;

	default:break;
	}
	return DefWindowProc(hWnd, uMsg, wp, lp);
}
