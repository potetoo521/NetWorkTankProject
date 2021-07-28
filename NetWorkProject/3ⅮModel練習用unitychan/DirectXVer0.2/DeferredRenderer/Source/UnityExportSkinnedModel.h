#pragma once
#include "DirectX11Manager.h"

class UnityExportSkinnedModel
{
	InputLayout il;
	VertexShader vs;
	PixelShader ps;

	ConstantBuffer boneMtxCb;
	XMMATRIX boneMtx[200];
public:

	//2021-07-12 月曜日
	XMFLOAT3 maxPos;//最大頂点
	XMFLOAT3 minPos;//最小頂点

	//2020-11-11 Wednesday
	//for BoundingBox データ 
	
	//XMFLOAT3 maxpos;// = XMFLOAT3(0, 0, 0);
	//XMFLOAT3 minpos;// = XMFLOAT3(0, 0, 0);


	//struct OBB {
	//	XMMATRIX m_WorldMatrix;
	//	XMVECTOR m_Pos;              // 位置
	//	XMVECTOR m_NormaDirect[3];   // 方向ベクトル
	//	FLOAT m_fLength[3];          // 各軸方向の長さ
	//} obb;
	////struct OBB {
	//	XMVECTOR vCenter;//BBox 中心点ベクトル
	//	XMVECTOR vDir[3];//BBox 方向ベクトル
	//	FLOAT	 fAxLen[3];//BBox Local座標軸の長さの半分				
	//} obb;

	struct VertexData
	{
		XMFLOAT3 position;
		XMFLOAT3 normal = XMFLOAT3(0, 0, 0);
		XMFLOAT2 uv = XMFLOAT2(0, 0);
		XMUINT4 boneIndex = XMUINT4(0, 0, 0, 0);
		XMFLOAT4 boneWeight = XMFLOAT4(0, 0, 0, 0);
	};

	struct Material
	{
		ShaderTexture albedoTexture;
	};

	struct ModelData
	{
		VertexBuffer vb;
		IndexBuffer ib;
	};

	uem::SkinnedModel<VertexData> uemData;

	vector<ModelData> models;
	vector<Material> materials;

	UnityExportSkinnedModel();

	void LoadAscii(string filename);
	void LoadBinary(string filename);

	//void DrawImGui(std::shared_ptr<uem::Transform> trans);
	void Draw();
};