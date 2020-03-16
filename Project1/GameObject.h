#pragma once
#include <DirectXTex.h>
#include<vector>
#include"ObjLoader.h"


class Material;
class Mesh;
class ObjLoader;
struct CustomVertex;
struct ConstantBufferForPerFrame;



class GameObject
{
public:
	GameObject();
	~GameObject();

	void Init(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext);
	void Update(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext);
	void Render(ID3D11DeviceContext* m_pDeviceContext, DirectX::XMMATRIX view, DirectX::XMMATRIX proj);
	void makeMVP(ConstantBufferForPerFrame* cb, float pos_x, float pos_y, float rot_z, DirectX::XMMATRIX m_View, DirectX::XMMATRIX m_Proj);

private:

	Material* material;
	Mesh* mesh;

	ObjLoader* objLoader;
	Data data;

	CustomVertex* vertices1;
	
	WORD* indexList1;
	

	float pos_x;
	float pos_y;
	float rot_z;

	D3D11_RASTERIZER_DESC rd;

	ID3D11Buffer* m_pCB;


};

