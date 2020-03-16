#include<Windows.h>
#include"App.h"
#include "renderdoc_app.h"

void GetRenderDoc();

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow
)
{
	GetRenderDoc();

	App* app;
	app = new App();

	app->Run();

	delete(app);

	return 0;
}

void GetRenderDoc()
{
	static RENDERDOC_API_1_1_2*  m_api = nullptr;
	static HMODULE m_module_handle = nullptr;
	static bool m_is_active = false;

	m_module_handle = LoadLibrary("../RenderDoc\\renderdoc.dll");
	if (m_module_handle)
	{
		pRENDERDOC_GetAPI getterApi = (pRENDERDOC_GetAPI)GetProcAddress(m_module_handle, "RENDERDOC_GetAPI");
		int32_t result = getterApi(eRENDERDOC_API_Version_1_1_2, (void**)&m_api);
		if (result != 1)
		{
			FreeLibrary(m_module_handle);
		}
	}
}