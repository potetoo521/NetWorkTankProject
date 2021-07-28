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

	//2021-07-12 ���j��
	XMFLOAT3 maxPos;//�ő咸�_
	XMFLOAT3 minPos;//�ŏ����_

	//2020-11-11 Wednesday
	//for BoundingBox �f�[�^ 
	
	//XMFLOAT3 maxpos;// = XMFLOAT3(0, 0, 0);
	//XMFLOAT3 minpos;// = XMFLOAT3(0, 0, 0);


	//struct OBB {
	//	XMMATRIX m_WorldMatrix;
	//	XMVECTOR m_Pos;              // �ʒu
	//	XMVECTOR m_NormaDirect[3];   // �����x�N�g��
	//	FLOAT m_fLength[3];          // �e�������̒���
	//} obb;
	////struct OBB {
	//	XMVECTOR vCenter;//BBox ���S�_�x�N�g��
	//	XMVECTOR vDir[3];//BBox �����x�N�g��
	//	FLOAT	 fAxLen[3];//BBox Local���W���̒����̔���				
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