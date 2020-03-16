#include "Mesh.h"



Mesh::Mesh()
	:
	m_Vertices(nullptr),
	m_indexList(nullptr),
	m_VertexCount(0),
	m_IndexCount(0),
	m_pVB(nullptr),
	m_pIB(nullptr)
{
}


Mesh::~Mesh()
{
	delete(m_Vertices);
	delete(m_indexList);
	if (m_pVB)
	{
		m_pVB->Release();
		m_pVB = NULL;
	}


	if (m_pIB)
	{
		m_pIB->Release();
		m_pIB = NULL;
	}
}


void Mesh::SetVerticesAndCount(CustomVertex* vertices, int count)
{
	m_VertexCount = count;
	m_Vertices = new CustomVertex[m_VertexCount];
	for (int i = 0; i < m_VertexCount; i++)
	{
		m_Vertices[i] = vertices[i];
	}

}

void Mesh::SetIndexListAndCount(WORD* indexList, int count)
{
	m_IndexCount = count;
	m_indexList = new WORD[m_IndexCount];
	for (int i = 0; i < m_IndexCount; i++)
	{
		m_indexList[i] = indexList[i];
	}
}


bool Mesh::SetBuffer(ID3D11Device* m_pDevice, ID3D11DeviceContext* m_pDeviceContext)
{


	{
		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CustomVertex) * m_VertexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
		initData.pSysMem = m_Vertices;
		HRESULT hr = m_pDevice->CreateBuffer(&bd, &initData, &m_pVB);
		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreateBuffer() Failed.");
			return false;
		}

	}

	{

		D3D11_BUFFER_DESC bd;
		ZeroMemory(&bd, sizeof(D3D11_BUFFER_DESC));
		bd.Usage = D3D11_USAGE_DEFAULT;
		bd.ByteWidth = sizeof(CustomVertex) * m_IndexCount;
		bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		bd.CPUAccessFlags = 0;

		D3D11_SUBRESOURCE_DATA initData;
		ZeroMemory(&initData, sizeof(D3D11_SUBRESOURCE_DATA));
		initData.pSysMem = m_indexList;

		HRESULT hr = m_pDevice->CreateBuffer(&bd, &initData, &m_pIB);
		if (FAILED(hr))
		{
			assert(false && "ID3D11Device::CreateIndexBuffer() Failed.");
			return false;
		}

	}


	return true;
}

void Mesh::Render(ID3D11DeviceContext* m_pDeviceContext, DirectX::XMMATRIX view, DirectX::XMMATRIX proj)
{
	UINT stride = sizeof(CustomVertex);
	UINT offset = 0;
	m_pDeviceContext->IASetVertexBuffers(0, 1, &m_pVB, &stride, &offset);
	m_pDeviceContext->IASetIndexBuffer(m_pIB, DXGI_FORMAT_R16_UINT, 0);

	//m_pDeviceContext->Draw(m_VertexCount, 0);
	m_pDeviceContext->DrawIndexed(m_IndexCount, 0, 0);
}