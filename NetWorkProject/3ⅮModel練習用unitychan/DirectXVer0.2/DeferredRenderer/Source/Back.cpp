//---------------------------------------------
// Back.cpp
// 2021-04-17 Saturday �E��ɔz�u�i���ی��j
//---------------------------------------------
//�x����\��
#pragma warning(disable : 4005)
#pragma warning(disable : 4838)

#include "DirectX11Manager.h"

#include "Back.h"

#include "Camera.h"

extern DirectX11Manager g_DX11Manager;

extern ConstantBufferMatrix consBufferMatrix;
extern ConstantBuffer cbuffer;


//---------------------------------------------
// ���_���C�A�E�g Start 2020-11-03 Tuesday
//---------------------------------------------
D3D11_INPUT_ELEMENT_DESC g_layout[] =
{
	{"POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "NORMAL"	,	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	{ "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	32,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
};

UINT g_numElements = ARRAYSIZE(g_layout);



//2020-06-21 Sunday �ǉ�
D3D11_INPUT_ELEMENT_DESC* getLayout() {

	return g_layout;
}

UINT getNumElement() {

	return g_numElements;
}

//---------------------------------------------
// ���_���C�A�E�g End 2020-11-03 Tuesday
//---------------------------------------------


CBack* getBack() {
	
	static CBack* back = nullptr;

	if (back == nullptr) {

		back = new CBack();
	}
	return back;
}

CBack::CBack() {
	
}

struct CBack::TransInfo* CBack::getTInfo() {

	static struct TransInfo info;

	info.life = 0;
	info.Pos = XMVectorSet(0, 0, 0, 1);
	info.Dir = XMVectorSet(0, 0, 1, 1);
	info.Vel = XMVectorSet(0, 0, 1, 1);
	info.WVP = XMMatrixIdentity();
	info.matScale = XMMatrixIdentity();
	info.matRot = XMMatrixIdentity();
	info.matTrans = XMMatrixIdentity();

	info.matWorld = XMMatrixIdentity();


	return &info;
}

void CBack::Init() {

	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	
	CBack* back = getBack();

	
	//�V�F�[�_�[Attach
	vs.Attach(g_DX11Manager.CreateVertexShader("Assets/Shaders/UnityExportModel.hlsl", "vsMain"));
	ps.Attach(g_DX11Manager.CreatePixelShader("Assets/Shaders/UnityExportModel.hlsl", "psMain"));

	//-----------------------------------------
	// Particle�e�N�X�`���ǂݍ���
	//-----------------------------------------
	//�}�e���A���i�e�N�X�`���jAttach	
	Material tmpMaterial;
	tmpMaterial.albedoTexture.Attach
	(g_DX11Manager.CreateTextureFromFile("Assets/spaceship.jpg"));
		//�}�e���A���R���e�i�[�Ɋi�[
	materials.push_back(tmpMaterial);
	
	//-----------------------------------------
	// Particle 1�@���_�o�b�t�@�쐬
	//-----------------------------------------
	//Create the vertex buffer
	float ux = 0;// 
	float vy = 0;// 

	float uw = 1.0f;// 
	float vh = 1.0f;// 
	float w = 12;// 72 / 2;// (float)454 / 2;
	float h = 12;// 72 / 2;// (float)340;

	static float stscale = 2.0f;
	VertexData v[] =
	{
		// X-Y Face
		{{-w,  0, h},   { -w, -1, h},{ux,		vy}},		//����
		{{ w,  0, h},   {  w, -1, h},{ux + uw,	vy}},		//�E��
		{{ w,  0,  0},  {  w, -1, 0},{ux + uw,	vy + vh}},	//�E��
		{{-w,  0,  0},  {  0, -1, 0},{ux,		vy + vh}}	//����
	};
	
	UINT indices[] = {
		0,  1,  2,
		0,  2,  3,
	};

	//-----------------------------------------
	// Create the Input Layout 
	// �C���v�b�g���C�A�E�g�쐬
	// 2020-06-21 Sunday
	//-----------------------------------------

	D3D11_INPUT_ELEMENT_DESC* layout = getLayout();
	//�C���v�b�g���C�A�E�gAttach
	back->il.Attach(g_DX11Manager.CreateInputLayout(g_layout,g_numElements,
		"Assets/Shaders/UnityExportModel.hlsl", "vsMain"));

	//--------------------------------------------
	// Vertex�o�b�t�@�쐬�@
	//--------------------------------------------

	//--------------------------------------------
	// Index�o�b�t�@�쐬�@
	//--------------------------------------------
	//���f���f�[�^Attach
	ModelData tmpdata;

	tmpdata.ib.Attach(g_DX11Manager.CreateIndexBuffer(indices,6));//3�~2
	
	tmpdata.vb.Attach(g_DX11Manager.CreateVertexBuffer(v, 6));//���`�̒��_
	
	//���f���R���e�i�[�Ɋi�[
	back->models.push_back(tmpdata);
		
	//�|���S���g�|���W�[�@TriangleList
	//Set Primitive Topology
	g_DX11Manager.m_pImContext->IASetPrimitiveTopology(
		D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
}


void CBack::Update() {

	
}


void CBack::Draw() {
	
	//�V�F�[�_�[�Z�b�g
	g_DX11Manager.SetVertexShader(vs.Get());
	g_DX11Manager.SetPixelShader(ps.Get());
	//�C���v�b�g���C�A�E�g�Z�b�g
	g_DX11Manager.SetInputLayout(il.Get());

	//���_�o�b�t�@�A�C���f�b�N�X�o�b�t�@�Z�b�g
	g_DX11Manager.SetVertexBuffer(models[0].vb.Get(), sizeof(VertexData));
	g_DX11Manager.SetIndexBuffer( models[0].ib.Get());
	g_DX11Manager.SetTexture2D(0, materials[0].albedoTexture.Get());
	
	static float angley = 0;// -(float)XM_PI / 2;
	
	struct CBack::TransInfo* info = getTInfo();

	info->matRot = XMMatrixRotationY(angley);
		
	for (int i = 0; i < 2; i++) {
		info->matScale = XMMatrixScaling(1, 1, 1);

		info->matTrans =
			XMMatrixTranslation( 0, 0, 0);

		info->matWorld =
			info->matScale * info->matRot *
			info->matTrans;
		// Object���́AmatWorld��萔�o�b�t�@�ɐݒ�
		consBufferMatrix.world = XMMatrixTranspose(
			info->matWorld);

		//GPU�ɒ萔�o�b�t�@��]��
		g_DX11Manager.UpdateConstantBuffer(
			cbuffer.Get(), consBufferMatrix);

		//Back Draw
		g_DX11Manager.DrawIndexed(6);
	}

}
		
