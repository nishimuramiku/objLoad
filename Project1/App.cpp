#include "App.h"
#include"Device.h"
#include"Scene.h"




App::App()
	:window(nullptr),
	device(nullptr),
	scene(nullptr)
{
}

App::~App()
{
	delete(device);
	delete(window);
	delete(scene);
}

bool App::InitD3D11()
{
	HRESULT hr = CoInitializeEx(nullptr, COINITBASE_MULTITHREADED);

	RECT rc;
	GetClientRect(window->GethWnd(), &rc);

	UINT w = rc.right - rc.left;
	UINT h = rc.bottom - rc.top;
	FLOAT m_AspectRatio = (FLOAT)w / (FLOAT)h;

	scene = new Scene();
	device = new Device(window);

	if (!device->CreateSwapchain())
	{
		return false;
	}

	device->InitDeviceContext();


	if (!scene->Init(device, m_AspectRatio))
	{
		return false;
	}

	return true;
}

bool App::InitApp()
{

	window = new Window(config);

	if (!window->InitWnd())
	{
		return false;
	}
	if (!InitD3D11())
	{
		return false;
	}
	return true;
}


int App::Run()
{
	int retcode = -1;

	if (InitApp())
	{
		retcode = MainLoop();
	}
	return retcode;
}

int App::MainLoop()
{
	MSG msg = { 0 };
	while (WM_QUIT != msg.message)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			if (GetKeyState(VK_SPACE) & 0x8000)
			{
				break;
			}
			scene->Update();
			Render();

		}
	}
	return (int)msg.wParam;
}

void App::Render()
{
	device->Begin();
	scene->Render(device);
	IDXGISwapChain* m_pSwapChain;
	device->GetSwapChain(&m_pSwapChain);
	m_pSwapChain->Present(0, 0);

}