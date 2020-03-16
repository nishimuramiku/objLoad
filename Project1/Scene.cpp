#include "Scene.h"
#include"Device.h"
#include"Material.h"
#include"GameObject.h"


Scene::Scene()
	:oinusama(nullptr),
	m_pDevice(nullptr),
	m_pDeviceContext(nullptr)
{
	m_View = DirectX::XMMatrixIdentity();
	m_Proj = DirectX::XMMatrixIdentity();
}

Scene::~Scene()
{
	delete(oinusama);
	m_pDevice->Release();
	m_pDeviceContext->Release();

}


bool Scene::Init(Device* device, const FLOAT aspectRatio)
{

	device->GetDevice(&m_pDevice);
	device->GetDeviceContext(&m_pDeviceContext);

	oinusama = new GameObject();
	oinusama->Init(m_pDevice, m_pDeviceContext);

	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(1.0f, 0.0f, -0.75f, 1.0f);
	DirectX::XMVECTOR camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR camUpward = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);//default


	m_View = DirectX::XMMatrixLookAtLH(camPos, camTarget, camUpward);
	m_Proj = DirectX::XMMatrixPerspectiveFovLH(DirectX::XM_PIDIV2, aspectRatio, 0.01f, 1000.0f);


	return true;
}

void Scene::Update()
{
	

	if (GetKeyState(VK_NUMPAD1) & 0x8000) {
		cam_x += 0.0005f;
	}



	if (GetKeyState(VK_NUMPAD2) & 0x8000) {
		cam_y += 0.0005f;
	}

	if (GetKeyState(VK_NUMPAD3) & 0x8000) {
		cam_z  += 0.0005f;
	}

	if (GetKeyState(VK_NUMPAD4) & 0x8000) {
		cam_x -= 0.0005f;
	}



	if (GetKeyState(VK_NUMPAD5) & 0x8000) {
		cam_y -= 0.0005f;
	}

	if (GetKeyState(VK_NUMPAD6) & 0x8000) {
		cam_z -= 0.0005f;
	}




	DirectX::XMVECTOR camPos = DirectX::XMVectorSet(cam_x, cam_y, cam_z, 1.0f);
	DirectX::XMVECTOR camTarget = DirectX::XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f);
	DirectX::XMVECTOR camUpward = DirectX::XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);//default
	m_View = DirectX::XMMatrixLookAtLH(camPos, camTarget, camUpward);

	oinusama->Update(m_pDevice, m_pDeviceContext);

}

void Scene::Render(Device* device)
{
	device->GetDevice(&m_pDevice);
	device->GetDeviceContext(&m_pDeviceContext);

	oinusama->Render(m_pDeviceContext, m_View, m_Proj);

}