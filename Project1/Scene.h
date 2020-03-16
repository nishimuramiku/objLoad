#pragma once
#include<DirectXmath.h>
#include<d3d11.h>

#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"d3dcompiler.lib")

class Device;
class GameObject;

class Scene
{
public:
	Scene();
	~Scene();
	bool Init(Device* device, const FLOAT aspectRatio);
	void Update();
	void Render(Device* device);


private:
	GameObject* oinusama;

	ID3D11Device* m_pDevice;
	ID3D11DeviceContext* m_pDeviceContext;

	DirectX::XMMATRIX m_View;
	DirectX::XMMATRIX m_Proj;

	float cam_x = 1.0f;
	float cam_y = 0.0f;
	float cam_z = -0.75f;

};