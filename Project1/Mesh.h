#pragma once

#include<d3d11.h>
#include<DirectXmath.h>

struct CustomVertex
{
	DirectX::XMFLOAT3 position;
	DirectX::XMFLOAT2 texcoord;
	DirectX::XMFLOAT4 color;
};

struct ConstantBufferForPerFrame
{
	DirectX::XMMATRIX world;
	DirectX::XMMATRIX view;
	DirectX::XMMATRIX proj;
	DirectX::XMMATRIX mvp;


};

class Mesh
{
public:
	Mesh();
	~Mesh();

	void SetVerticesAndCount(CustomVertex* vertices, int count);
	void SetIndexListAndCount(WORD* indexList, int count);
	bool SetBuffer(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext);
	void Render(ID3D11DeviceContext* m_pDeviceContext, DirectX::XMMATRIX view, DirectX::XMMATRIX proj);



private:
	CustomVertex *m_Vertices;
	WORD *m_indexList;
	int m_VertexCount;
	int m_IndexCount;


	ID3D11Buffer* m_pVB;
	ID3D11Buffer* m_pIB;

};