#include "GameObject.h"
#include"Material.h"
#include"Mesh.h"
#include"ObjLoader.h"

#include<iostream>


GameObject::GameObject()
	:material(nullptr),
	mesh(nullptr),
	objLoader(nullptr),
	vertices1(nullptr),
	indexList1(nullptr),
	m_pCB(nullptr),
	pos_x(0.0f),
	pos_y(0.0f),
	rot_z(0.0f)
{
}


GameObject::~GameObject()
{
	delete material;
	delete mesh;
	delete objLoader;
	delete vertices1;
	delete indexList1;
	if (m_pCB)
	{
		m_pCB->Release();
		m_pCB = nullptr;
	}
}

void GameObject::Init(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{
	const char* fileName = "cube.obj";
	objLoader = new ObjLoader();

	objLoader->OpenFile(fileName);
	objLoader->LoadObj(&data);


	ZeroMemory(&rd, sizeof(D3D11_RASTERIZER_DESC));
	rd.CullMode = D3D11_CULL_NONE;
	//rd.FillMode = D3D11_FILL_SOLID;
	rd.FillMode = D3D11_FILL_WIREFRAME;
	rd.DepthClipEnable = TRUE;

	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.ByteWidth = sizeof(ConstantBufferForPerFrame);
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
		bd.CPUAccessFlags = 0;

		HRESULT hr = m_pDevice->CreateBuffer(&bd, NULL, &m_pCB);
		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreateBuffer() Failed.");
		}
	}

	material = new Material();

	material->createMaterial(
		m_pDevice,
		m_pDeviceContext,
		L"img.png",
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		rd,
		L"Simple.fx",
		"VSFunc",
		L"Simple.fx",
		"PSFunc");

	

	int size = data.v.size();
	vertices1 = new CustomVertex[size];

	for (int i = 0; i < size; i++)
	{
		vertices1[i].position = DirectX::XMFLOAT3(data.v[i][0], data.v[i][1], data.v[i][2]);
		vertices1[i].texcoord = DirectX::XMFLOAT2(data.vt[i][0], data.vt[i][1]);
		vertices1[i].color = DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f);

	}

	size = data.f.size() / 12;

	indexList1 = new WORD[2 * 3 * size];

	for (int i = 0; i < size ; i++)
	{
		/*indexList1[i * 6 + 0] = data.f[i * 6 + 3 * 0] - 1;
		indexList1[i * 6 + 1] = data.f[i * 6 + 3 * 1] - 1;
		indexList1[i * 6 + 2] = data.f[i * 6 + 3 * 2] - 1;
		indexList1[i * 6 + 3] = data.f[i * 6 + 3 * 1] - 1;
		indexList1[i * 6 + 4] = data.f[i * 6 + 3 * 2] - 1;
		indexList1[i * 6 + 5] = data.f[i * 6 + 3 * 3] - 1;*/

		indexList1[i * 6 + 0] = data.f[i * 12 + 3 * 0] - 1;
		indexList1[i * 6 + 1] = data.f[i * 12+ 3 * 2] - 1;
		indexList1[i * 6 + 2] = data.f[i * 12 + 3 * 1] - 1;
		indexList1[i * 6 + 3] = data.f[i * 12 + 3 * 0] - 1;
		indexList1[i * 6 + 4] = data.f[i * 12 + 3 * 2] - 1;
		indexList1[i * 6 + 5] = data.f[i * 12 + 3 * 3] - 1;

	}

	//SetŒnnew‚µ‚Ä‚¢‚é‚Ì‚Å’ˆÓ
	mesh = new Mesh();
	mesh->SetIndexListAndCount(indexList1, 2 * 3 * size);
	mesh->SetVerticesAndCount(vertices1, 8);
	mesh->SetBuffer(m_pDevice, m_pDeviceContext);

}

void GameObject::Update(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{
	if (GetKeyState('W') & 0x8000) {
		pos_y += 0.0001f;
	}



	if (GetKeyState('S') & 0x8000) {
		pos_y -= 0.0001f;
	}

	if (GetKeyState('D') & 0x8000) {
		pos_x += 0.0001f;
	}

	if (GetKeyState('A') & 0x8000) {
		pos_x -= 0.0001f;
	}


	if (GetKeyState('R') & 0x8000) {
		pos_x = 0.0f;
		pos_y = 0.0f;
		rot_z = 0.0f;

	}

	if (GetKeyState(VK_SPACE) & 0x8000) {
		material->releaseMaterial();
		material->createMaterial(m_pDevice,
			m_pDeviceContext,
			L"img2.png",
			D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP,
			rd,
			L"Simple.fx",
			"VSFunc",
			L"Simple.fx",
			"PSFunc");
	}
}

void GameObject::Render(ID3D11DeviceContext* m_pDeviceContext, DirectX::XMMATRIX view, DirectX::XMMATRIX proj)
{
	ConstantBufferForPerFrame cb;
	makeMVP(&cb, pos_x, pos_y, rot_z, view, proj);
	m_pDeviceContext->UpdateSubresource(m_pCB, 0, NULL, &cb, 0, 0);
	m_pDeviceContext->VSSetConstantBuffers(0, 1, &m_pCB);
	mesh->Render(m_pDeviceContext, view, proj);
	

}

void GameObject::makeMVP(ConstantBufferForPerFrame* cb, float pos_x, float pos_y, float rot_z, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj)
{
	DirectX::XMMATRIX MVP;
	DirectX::XMMATRIX g_matrix;
	DirectX::XMMATRIX t_matrix;
	DirectX::XMFLOAT3 g_pos = { pos_x, pos_y, 0 };
	DirectX::XMFLOAT3 g_rot = { 0,0,rot_z };
	DirectX::XMFLOAT3 g_scal = { 0.5f,0.5f,0.5f };

	g_matrix = DirectX::XMMatrixIdentity();
	t_matrix = DirectX::XMMatrixIdentity();

	g_matrix = DirectX::XMMatrixScaling(g_scal.x, g_scal.y, g_scal.z);

	t_matrix = DirectX::XMMatrixRotationRollPitchYaw(g_rot.x, g_rot.y, g_rot.z);

	g_matrix *= t_matrix;

	t_matrix = DirectX::XMMatrixTranslation(g_pos.x, g_pos.y, g_pos.z);

	g_matrix *= t_matrix;


	MVP = DirectX::XMMatrixIdentity();
	MVP *= g_matrix;
	MVP *= m_View;
	MVP *= m_Proj;


	cb->world = g_matrix;
	cb->view = m_View;
	cb->proj = m_Proj;
	cb->mvp = MVP;



}

