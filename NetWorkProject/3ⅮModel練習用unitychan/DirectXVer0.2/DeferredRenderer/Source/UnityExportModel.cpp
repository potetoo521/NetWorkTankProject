#include "UnityExportModel.h"

UnityExportModel::UnityExportModel()
{
	//vs.Attach(g_DX11Manager.CreateVertexShader("Assets/Shaders/UnityExportModel.hlsl", "vsMain"));
	//ps.Attach(g_DX11Manager.CreatePixelShader("Assets/Shaders/UnityExportModel.hlsl", "psMain"));

	////InputLayout�̍쐬
	//D3D11_INPUT_ELEMENT_DESC elem[] = {
	//	{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	//	{ "NORMAL"	,	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	//	{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	//	{ "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	32,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	//};
	//il.Attach(g_DX11Manager.CreateInputLayout(elem, 4, "Assets/Shaders/UnityExportModel.hlsl", "vsMain"));
}

void UnityExportModel::LoadAscii(string filename)
{
	uemData.LoadAscii(filename);

	//VertexBuffer IndexBuffer�쐬
	for (auto& mesh : uemData.meshs)
	{
		ModelData tmpData;
		tmpData.vb.Attach(g_DX11Manager.CreateVertexBuffer(mesh.vertexDatas.data(), (UINT)mesh.vertexDatas.size()));
		tmpData.ib.Attach(g_DX11Manager.CreateIndexBuffer(mesh.indexs.data(), (UINT)mesh.indexs.size()));
		models.push_back(tmpData);
	}

	//TextureLoad
	for (auto& material : uemData.materials)
	{
		Material tmpMaterial;
		
		tmpMaterial.albedoTexture.Attach(
			g_DX11Manager.CreateTextureFromFile(material.GetTexture("_MainTex")));
		materials.push_back(tmpMaterial);
	}
}

void UnityExportModel::LoadBinary(string filename)
{
	//attach�̏ꏊ���R���X�g���N�^�[����ړ�
	//2020-11-18 Wednesday
	//shader�̃R���p�C����x�������邽��
	//device���ł��Ă���
	
	vs.Attach(g_DX11Manager.CreateVertexShader("Assets/Shaders/UnityExportModel.hlsl", "vsMain"));
	ps.Attach(g_DX11Manager.CreatePixelShader("Assets/Shaders/UnityExportModel.hlsl", "psMain"));
	//InputLayout�̍쐬
	D3D11_INPUT_ELEMENT_DESC elem[] = {
		{ "POSITION",	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL"	,	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD",	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "COLOR"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	32,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};
	il.Attach(g_DX11Manager.CreateInputLayout(elem, 4,
		"Assets/Shaders/UnityExportModel.hlsl", "vsMain"));
	
	uemData.LoadBinary(filename);

	//--------------------------------------------
	//  Model ���_�f�[�^�擾�@Max and Min
	// 	Model ���@�����@���s Get
	//--------------------------------------------
	//static XMFLOAT3 maxPos(0,0,0);
	//static XMFLOAT3 minPos(0,0,0);
	static XMFLOAT3 mlen(0,0,0);//w,h,z
	float vx, vy, vz;

	//VertexBuffer IndexBuffer�쐬
	for (auto& mesh : uemData.meshs)
	{
		ModelData tmpData;//
		//Vertex Data Get
		vx = mesh.vertexDatas.data()->position.x;
		vy = mesh.vertexDatas.data()->position.y;
		vz = mesh.vertexDatas.data()->position.z;

		if (maxPos.x < vx) maxPos.x = vx;
		if (maxPos.y < vy) maxPos.y = vy;
		if (maxPos.z < vz) maxPos.z = vz;

		if (minPos.x > vx) minPos.x = vx;
		if (minPos.y > vy) minPos.y = vy;
		if (minPos.z > vz) minPos.z = vz;

		
	    //mesh.vertexDatas.data()->position
		tmpData.vb.Attach(g_DX11Manager.CreateVertexBuffer(mesh.vertexDatas.data(), (UINT)mesh.vertexDatas.size()));
		tmpData.ib.Attach(g_DX11Manager.CreateIndexBuffer(mesh.indexs.data(), (UINT)mesh.indexs.size()));
		models.push_back(tmpData);
		
	}
	
	mlen.x = fabs(maxPos.x - minPos.x);
	mlen.y = fabs(maxPos.y - minPos.y);
	mlen.z = fabs(maxPos.z - minPos.z);
    
	char str[256];

	sprintf(str, "-------------------------------\n");
	OutputDebugString(str);
	sprintf(str, "%s,model.w=%f,model.h=%f,model.z=%f\n",filename.c_str(), mlen.x, mlen.y, mlen.z);
	OutputDebugString(str);

	sprintf(str, "-------------------------------\n");
	OutputDebugString(str);

	//TextureLoad
	for (auto& material : uemData.materials)
	{
		Material tmpMaterial;
		tmpMaterial.albedoTexture.Attach(g_DX11Manager.CreateTextureFromFile(material.GetTexture("_MainTex")));
		materials.push_back(tmpMaterial);
	}
}

void UnityExportModel::Draw()
{
	g_DX11Manager.SetVertexShader(vs.Get());
	g_DX11Manager.SetPixelShader(ps.Get());

	g_DX11Manager.SetInputLayout(il.Get());

	for (int i = 0; i < uemData.meshs.size();i++) {
		auto& model = uemData.meshs[i];
		g_DX11Manager.SetVertexBuffer(models[i].vb.Get(), sizeof(VertexData));
		g_DX11Manager.SetIndexBuffer(models[i].ib.Get());
		if (materials[model.materialNo].albedoTexture.Get() != nullptr)
			g_DX11Manager.SetTexture2D(0, 
				materials[model.materialNo].albedoTexture.Get());

		//DrawCall
		g_DX11Manager.DrawIndexed(static_cast<UINT>(model.indexs.size()));
	}
}
