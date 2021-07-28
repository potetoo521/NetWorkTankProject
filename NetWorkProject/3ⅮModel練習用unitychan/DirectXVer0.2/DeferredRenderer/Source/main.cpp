//---------------------------------------------
// unitychan 表示
// UniModelExportライブラリー
// DirectX11
// x64 Visual Studio 2019
// 2021-06-27 Sunday
//---------------------------------------------
#include "DirectX11Manager.h"
#include "UnityExportModel.h"
#include "UnityExportSkinnedModel.h"
#include "Camera.h"

#include "Player.h"//unitychan
#include "Back.h"

#include "D3D11Font.h"
//#include <tchar.h>
//入力
#include "input.h"
//サウンドXAudio2.hを使用
#include "Audio2.h"



//---------------------------------------------
// User 定義　エリア Start
//---------------------------------------------
#define SCREEN_WIDTH 1270.0f//pixel 画面横幅
#define SCREEN_HEIGHT 760.0f//pixel 画面高さ

//---------------------------------------------
// User 定義　エリア　End
//---------------------------------------------
//---------------------------------------------
// GPUにMatrixを転送する定数バッファ
//---------------------------------------------
ConstantBufferMatrix consBufferMatrix;
ConstantBuffer cbuffer;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//-----------------------------------------
	// DirectX11初期化
	//-----------------------------------------
	LONGLONG NowTime;
	LONGLONG Time;
	float DeltaTime;
	int FPS;
	int FPSCounter;
	LONGLONG FPSCheckTime;

	if (FAILED(g_DX11Manager.Init(hInstance, nCmdShow)))
		return -1;
	//Windows Message 定義
	MSG msg = { 0 };

	


	

	//--------------------------------------------
	// Model 宣言 2021-05-04 Tuesday
	//--------------------------------------------
	
	
	//--------------------------------------------
	// Block Model
	//--------------------------------------------
	
	UnityExportModel BlockModel;

	BlockModel.LoadBinary("Assets/Block/MeshData.umb");
	
	
	//--------------------------------------------
	// コンスタントバッファの作成
	//--------------------------------------------
	g_DX11Manager.CreateConstantBuffer(
		sizeof(ConstantBufferMatrix), &cbuffer);
	//--------------------------------------------
	// IMGUIの初期化
	//--------------------------------------------
	ImGui_ImplDX11_NewFrame();
	//-----------------------------------------
	// Camera 初期化 
	//-----------------------------------------
	CameraInit();
	//--------------------------------------------
	//プロジェクションMatrix（透視投影）作成
	//--------------------------------------------
	//GPUに定数バッファを渡すために、転置行列作成
	//Cameraの、viewMatrix,projMatrixを転置

	struct Camera* camera = getCamera();

	//プロジェクションMatrix(透視投影Matrix)
	consBufferMatrix.proj = XMMatrixTranspose(

		camera->projMatrix);
	//ビューMatrix(視野Matrix)
	consBufferMatrix.view = XMMatrixTranspose(
		camera->viewMatrix);

	//-----------------------------------------
	// キーボード、マウス初期化
	//-----------------------------------------

	InitInput(hInstance, g_DX11Manager.GetHWnd());

	//-----------------------------------------
	// 背景のロード
	//-----------------------------------------
	CBack* back = getBack();
	
	back->Init();
		
	//-----------------------------------------
	// Modelのロード
	//-----------------------------------------

	
	//--------------------------------------------
	// Unitychan 読み込み　Now Loading
	//--------------------------------------------
	Player* player = GetPlayer();
	
	player->PlayerInit();


	//--------------------------------------------
	// XAudio2 初期化 2020-11-25 Wednesday
	//--------------------------------------------
	InitSound();
	//--------------------------------------------
	// XAudio2 Play Sound
	//--------------------------------------------

	PlaySound(SOUND_LABEL_BGM000);

	//-----------------------------------------
	// Fontの初期化
	//-----------------------------------------

	CD3D11Font* pFont = NULL;

	//  フォントの作成
	pFont = new CD3D11Font(g_DX11Manager.m_pImContext.Get());

	//-----------------------------------------
	// Game ループ（Window メッセージループ）
	//-----------------------------------------
		
	//Game Loop
	while (true)
	{
		
		//-------------------------------------
		// Windows Message ループ
		//-------------------------------------
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message) break;

		
		//-------------------------------------
		// Input 更新
		//-------------------------------------
		//g_DX11Manager.input.InputUpdate();
		UpdateInput();

		//-------------------------------------
		// Camera Work更新
		//-------------------------------------
		CameraUpdate();

		//View Matrix 作成
		camera->viewMatrix = XMMatrixLookAtLH(
			camera->eyePos, camera->targetPos,//camera->eyePos +
			//constantBuffer.view.r[2],
			camera->upVector);
		//転置行列　定数バッファに設定
		consBufferMatrix.view = XMMatrixTranspose(
			camera->viewMatrix);

		//GPUに定数バッファ（Matrix)を転送
		g_DX11Manager.UpdateConstantBuffer(
			cbuffer.Get(), consBufferMatrix);

		//-------------------------------------
		// DirectX11 描画開始
		//-------------------------------------
		g_DX11Manager.DrawBegin();

		//共有定数バッファをデバイスに設定
		ID3D11Buffer* tmpCb[] = { cbuffer.Get() };
		g_DX11Manager.m_pImContext->VSSetConstantBuffers(
			0, 1, tmpCb);

		//-------------------------------------
		// Backの描画 World 原点
		//-------------------------------------

		back->Draw();

		//
		XMMATRIX blockScaleMatrix =//拡大 スケーリング
			XMMatrixScaling(1, 1, 1);
		XMMATRIX blockTransMatrix= //移動 マトリクス
			XMMatrixTranslation(0, 0.5f, 0);//少し上に
			
		XMMATRIX blockWorldMatrix =
			blockScaleMatrix *
			blockTransMatrix;
				
		//転置行列　定数バッファに設定
		consBufferMatrix.world = XMMatrixTranspose(
			blockWorldMatrix);
		
		//new char[1];
		//GPUに定数バッファ（Matrix)を転送
		g_DX11Manager.UpdateConstantBuffer(
			cbuffer.Get(), consBufferMatrix);

						
		BlockModel.Draw();

		XMVECTOR beforePos = player->GetPos();

		XMFLOAT3 befpos;//(x,y,z) 前の位置

		XMStoreFloat3(&befpos, beforePos);//行列をfloat x,y,zに変換
	/*	befpos.x = beforePos.m128_f32[0];
		befpos.y = beforePos.m128_f32[1];
		befpos.z = beforePos.m128_f32[2];*/
		//unitychanの行と列をだしてみる
		//(0,0)ならば、ヒット
		//(0,0)の所にブロックがあるという前提
		int before_row = (int)(befpos.z / 1.0f);//行 縦 上プラス
		int before_col = (int)(befpos.x / 1.0f);//列 横 右プラス


		//unitychan 更新（走る、ジャンプ、アニメーション）-----------------------------------------
		player->PlayerUpdate();
		//-----------------------------------------------------------------------------------------


		XMVECTOR nowPos = player->GetPos();

		XMFLOAT3 nowfpos;//(x,y,z) 現在の位置

		XMStoreFloat3(&nowfpos, nowPos);//行列をfloat x,y,zに変換

		//unitychanの行と列をだしてみる
		//(0,0)ならば、ヒット
		//(0,0)の所にブロックがあるという前提
		int now_row = (int)(nowfpos.z / 1.0f);//行 縦 上プラス
		int now_col = (int)(nowfpos.x / 1.0f);//列 横 右プラス

		//ヒット判定
		if (now_row == 0 && now_col == 0) {

			//Unityちゃんがブロックに当たった
			//元の位置に戻す めり込み修正
			nowfpos.x = befpos.x;
			nowfpos.z = befpos.z;

			nowPos = XMLoadFloat3(&nowfpos);

			player->SetPos(nowPos);



		}



		//bool PlayerHit(XMFLOAT3 p_pos, XMFLOAT3 b_pos, float p_len, float b_len); //Boxとの当たり判定 

		player->PlayerAnimation();
		player->PlayerJump();

		//unitychan 描画
		player->PlayerDraw();

		//---------------------------------
		// フォントを描画
		//---------------------------------
		FLOAT x = 500.0f, y = 50.0f;
		TCHAR tmp[32] = "Unitychan Model";
		pFont->DrawAnkText(g_DX11Manager.m_pImContext.Get(), tmp,
			XMFLOAT4(0.2f, 0.5f, 1.0f, 0.75f), x, y);
		//---------------------------------
		// UIの描画
		//---------------------------------
		char str[256];

		XMFLOAT3 campos;

		XMStoreFloat3(&campos, camera->eyePos);

		sprintf_s(str, 256, "campos.x=%f y=%f z=%f\r\n, nowPosX=%f, nowPosZ=%f,\r\n, befPosX=%f, befPosZ=%f,\r\n",
			campos.x, campos.y, campos.z,nowfpos.x,nowfpos.z,befpos.x,befpos.z);


		ImGui::SetNextWindowSize(ImVec2(300, 120),
			0/*ImGuiSetCond_Once*/);
		//ImGui::SetWindowFontScale(2);

		ImGui::Begin("Camera eyePos", 0, 0/*&show_another_window*/);
		ImGui::BulletText(str);
		ImGui::End();

		//---------------------------------
		// Stage の描画　End
		//---------------------------------
		g_DX11Manager.DrawEnd();
		
	}

	//mciSendString("close backmusic", NULL, 0, NULL);
	//-----------------------------------------
	// メモリ解放 Start
	//-----------------------------------------
	UninitSound();
	UninitInput();
	
	if (pFont != nullptr) {
		delete(pFont);
	}
	
	
	if (back != nullptr) {

		delete back;
	}
	
	g_DX11Manager.Cleanup();

	//-----------------------------------------
	// メモリ解放 End
	//-----------------------------------------


	return msg.message;
	
}