#pragma once
#pragma comment(lib,"d3d11.lib")

#include<d3d11.h>
#include<d3dcompiler.h>

#include"Window.h"

class Device;
class Scene;

class App
{
public:
	App();
	~App();

	int Run();

private:
	bool InitApp();
	bool InitD3D11();
	int MainLoop();
	void Render();

private:
	Window* window;
	Device* device;
	Scene* scene;

	Window::Config config;


};