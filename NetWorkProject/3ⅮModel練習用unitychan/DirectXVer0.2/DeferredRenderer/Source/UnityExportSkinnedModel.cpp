#include "UnityExportSkinnedModel.h"

UnityExportSkinnedModel::UnityExportSkinnedModel()
{
	
}

void UnityExportSkinnedModel::LoadAscii(string filename)
{
	uemData.LoadAscii(filename);

	//VertexBuffer IndexBuffer作成
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
		tmpMaterial.albedoTexture.Attach(g_DX11Manager.CreateTextureFromFile(material.GetTexture("_MainTex")));
		materials.push_back(tmpMaterial);
	}
}

void UnityExportSkinnedModel::LoadBinary(string filename)
{
	//attachの場所をコンストラクターから移動
	//2020-11-18 Wednesday
	//shaderのコンパイルを遅延させるため
	//deviceができてから
			
	vs.Attach(g_DX11Manager.CreateVertexShader("Assets/Shaders/UnityExportSkinnedModel.hlsl", "vsMain"));
	ps.Attach(g_DX11Manager.CreatePixelShader("Assets/Shaders/UnityExportSkinnedModel.hlsl", "psMain"));
	//InputLayoutの作成
	D3D11_INPUT_ELEMENT_DESC elem[] = {
		{ "POSITION"	,	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	0,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "NORMAL"		,	0,	DXGI_FORMAT_R32G32B32_FLOAT,	0,	12,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "TEXCOORD"	,	0,	DXGI_FORMAT_R32G32_FLOAT,		0,	24,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "BONEINDEX"	,	0,	DXGI_FORMAT_R32G32B32A32_UINT,	0,	32,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
		{ "BONEWEIGHT"	,	0,	DXGI_FORMAT_R32G32B32A32_FLOAT,	0,	48,	D3D11_INPUT_PER_VERTEX_DATA,	0 },
	};
	il.Attach(g_DX11Manager.CreateInputLayout(elem, 5, "Assets/Shaders/UnityExportSkinnedModel.hlsl", "vsMain"));

	g_DX11Manager.CreateConstantBuffer(sizeof(XMMATRIX) * 200, &boneMtxCb);

	
	uemData.LoadBinary(filename);

	//--------------------------------------------
	//  頂点データ取得　Max and Min
	// 	Model 幅　高さ　奥行 Get
	//--------------------------------------------
	//static XMFLOAT3 maxPos(0, 0, 0);
	//static XMFLOAT3 minPos(0, 0, 0);
	static XMFLOAT3 mlen(0, 0, 0);//w,h,z
	float vx, vy, vz;

	//VertexBuffer IndexBuffer作成
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
	sprintf(str, "%s,model.w=%f,model.h=%f,model.z=%f\n", filename.c_str(), mlen.x, mlen.y, mlen.z);
	OutputDebugString(str);

	sprintf(str, "-------------------------------\n");
	OutputDebugString(str);

	//VertexBuffer IndexBuffer作成
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
		tmpMaterial.albedoTexture.Attach(g_DX11Manager.CreateTextureFromFile(material.GetTexture("_MainTex")));
		materials.push_back(tmpMaterial);
	}
}

void UnityExportSkinnedModel::Draw()
{
	g_DX11Manager.SetVertexShader(vs.Get());
	g_DX11Manager.SetPixelShader(ps.Get());

	g_DX11Manager.SetInputLayout(il.Get());

	for(int j=0;j<uemData.meshs.size();j++){
		auto& model = uemData.meshs[j];
		//ボーン行列を作る
		for (int i = 0; i < model.bones.size(); i++)
		{
			auto mat = model.bones[i].second->LocalToWorldMatrix();
			boneMtx[i] = XMMatrixTranspose(model.bones[i].first * mat);
		}
		g_DX11Manager.UpdateConstantBuffer(boneMtxCb.Get(), boneMtx);
		ID3D11Buffer* tmpCb[] = { boneMtxCb.Get() };
		g_DX11Manager.m_pImContext->VSSetConstantBuffers(1, 1, tmpCb);

		g_DX11Manager.SetVertexBuffer(models[j].vb.Get(), sizeof(VertexData));
		g_DX11Manager.SetIndexBuffer(models[j].ib.Get());
		if (materials[model.materialNo].albedoTexture.Get() != nullptr)
			g_DX11Manager.SetTexture2D(0, materials[model.materialNo].albedoTexture.Get());

		//DrawCall
		g_DX11Manager.DrawIndexed(static_cast<UINT>(model.indexs.size()));
	}
}
