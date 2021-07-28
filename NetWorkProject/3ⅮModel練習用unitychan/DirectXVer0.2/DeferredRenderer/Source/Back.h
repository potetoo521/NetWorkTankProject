//---------------------------------------------
// Back.h
// 2021-01-22 Sunday
//---------------------------------------------
#pragma once

#include <d3d11.h>
#include <DirectXMath.h>

using namespace DirectX;

//---------------------------------------------
// 背景Class
//---------------------------------------------

class CBack{
	
	ComPtr<ID3D11InputLayout >  il=nullptr;//インプットレイアウト
	ComPtr<ID3D11VertexShader>  vs=nullptr;
	ComPtr<ID3D11PixelShader >  ps=nullptr;
	
	struct TransInfo {
		XMVECTOR Pos = XMVectorSet(0, 0, 0, 1);
		XMVECTOR Dir = XMVectorSet(0, 0, 1, 1);
		XMVECTOR Vel = XMVectorSet(0, 0, 1, 1);
		int life = 0;

		XMMATRIX WVP = XMMatrixIdentity();
		
		XMMATRIX matWorld= XMMatrixIdentity();
		XMMATRIX matTrans= XMMatrixIdentity();
		XMMATRIX matScale= XMMatrixIdentity();
		XMMATRIX matRot= XMMatrixIdentity();
	};


public:
	
	struct VertexData
	{
		XMFLOAT3 position = XMFLOAT3(0, 0, 0);//2020-12-06 Sunday Init
		XMFLOAT3 normal   = XMFLOAT3(0, 0, 0);
		XMFLOAT2 uv       = XMFLOAT2(0, 0);
		//XMFLOAT4 color = XMFLOAT4(0, 0, 0, 0);
	};

	struct Material
	{
		ShaderTexture albedoTexture;
	};

	struct ModelData
	{
		VertexBuffer vb;
		IndexBuffer  ib;
	};

	vector<ModelData> models;
	vector<Material>  materials;

	CBack();

	~CBack() {
		
	}
	
	void Init();
	void Update();

	void Draw();
	
	struct TransInfo* getTInfo();
};


class CBack* getBack();

