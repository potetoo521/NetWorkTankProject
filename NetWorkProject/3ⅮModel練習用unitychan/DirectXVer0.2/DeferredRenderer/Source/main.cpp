//---------------------------------------------
// unitychan �\��
// UniModelExport���C�u�����[
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
//����
#include "input.h"
//�T�E���hXAudio2.h���g�p
#include "Audio2.h"



//---------------------------------------------
// User ��`�@�G���A Start
//---------------------------------------------
#define SCREEN_WIDTH 1270.0f//pixel ��ʉ���
#define SCREEN_HEIGHT 760.0f//pixel ��ʍ���

//---------------------------------------------
// User ��`�@�G���A�@End
//---------------------------------------------
//---------------------------------------------
// GPU��Matrix��]������萔�o�b�t�@
//---------------------------------------------
ConstantBufferMatrix consBufferMatrix;
ConstantBuffer cbuffer;


int WINAPI WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPSTR lpCmdLine, _In_ int nCmdShow)
{
	//-----------------------------------------
	// DirectX11������
	//-----------------------------------------
	LONGLONG NowTime;
	LONGLONG Time;
	float DeltaTime;
	int FPS;
	int FPSCounter;
	LONGLONG FPSCheckTime;

	if (FAILED(g_DX11Manager.Init(hInstance, nCmdShow)))
		return -1;
	//Windows Message ��`
	MSG msg = { 0 };

	


	

	//--------------------------------------------
	// Model �錾 2021-05-04 Tuesday
	//--------------------------------------------
	
	
	//--------------------------------------------
	// Block Model
	//--------------------------------------------
	
	UnityExportModel BlockModel;

	BlockModel.LoadBinary("Assets/Block/MeshData.umb");
	
	
	//--------------------------------------------
	// �R���X�^���g�o�b�t�@�̍쐬
	//--------------------------------------------
	g_DX11Manager.CreateConstantBuffer(
		sizeof(ConstantBufferMatrix), &cbuffer);
	//--------------------------------------------
	// IMGUI�̏�����
	//--------------------------------------------
	ImGui_ImplDX11_NewFrame();
	//-----------------------------------------
	// Camera ������ 
	//-----------------------------------------
	CameraInit();
	//--------------------------------------------
	//�v���W�F�N�V����Matrix�i�������e�j�쐬
	//--------------------------------------------
	//GPU�ɒ萔�o�b�t�@��n�����߂ɁA�]�u�s��쐬
	//Camera�́AviewMatrix,projMatrix��]�u

	struct Camera* camera = getCamera();

	//�v���W�F�N�V����Matrix(�������eMatrix)
	consBufferMatrix.proj = XMMatrixTranspose(

		camera->projMatrix);
	//�r���[Matrix(����Matrix)
	consBufferMatrix.view = XMMatrixTranspose(
		camera->viewMatrix);

	//-----------------------------------------
	// �L�[�{�[�h�A�}�E�X������
	//-----------------------------------------

	InitInput(hInstance, g_DX11Manager.GetHWnd());

	//-----------------------------------------
	// �w�i�̃��[�h
	//-----------------------------------------
	CBack* back = getBack();
	
	back->Init();
		
	//-----------------------------------------
	// Model�̃��[�h
	//-----------------------------------------

	
	//--------------------------------------------
	// Unitychan �ǂݍ��݁@Now Loading
	//--------------------------------------------
	Player* player = GetPlayer();
	
	player->PlayerInit();


	//--------------------------------------------
	// XAudio2 ������ 2020-11-25 Wednesday
	//--------------------------------------------
	InitSound();
	//--------------------------------------------
	// XAudio2 Play Sound
	//--------------------------------------------

	PlaySound(SOUND_LABEL_BGM000);

	//-----------------------------------------
	// Font�̏�����
	//-----------------------------------------

	CD3D11Font* pFont = NULL;

	//  �t�H���g�̍쐬
	pFont = new CD3D11Font(g_DX11Manager.m_pImContext.Get());

	//-----------------------------------------
	// Game ���[�v�iWindow ���b�Z�[�W���[�v�j
	//-----------------------------------------
		
	//Game Loop
	while (true)
	{
		
		//-------------------------------------
		// Windows Message ���[�v
		//-------------------------------------
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (WM_QUIT == msg.message) break;

		
		//-------------------------------------
		// Input �X�V
		//-------------------------------------
		//g_DX11Manager.input.InputUpdate();
		UpdateInput();

		//-------------------------------------
		// Camera Work�X�V
		//-------------------------------------
		CameraUpdate();

		//View Matrix �쐬
		camera->viewMatrix = XMMatrixLookAtLH(
			camera->eyePos, camera->targetPos,//camera->eyePos +
			//constantBuffer.view.r[2],
			camera->upVector);
		//�]�u�s��@�萔�o�b�t�@�ɐݒ�
		consBufferMatrix.view = XMMatrixTranspose(
			camera->viewMatrix);

		//GPU�ɒ萔�o�b�t�@�iMatrix)��]��
		g_DX11Manager.UpdateConstantBuffer(
			cbuffer.Get(), consBufferMatrix);

		//-------------------------------------
		// DirectX11 �`��J�n
		//-------------------------------------
		g_DX11Manager.DrawBegin();

		//���L�萔�o�b�t�@���f�o�C�X�ɐݒ�
		ID3D11Buffer* tmpCb[] = { cbuffer.Get() };
		g_DX11Manager.m_pImContext->VSSetConstantBuffers(
			0, 1, tmpCb);

		//-------------------------------------
		// Back�̕`�� World ���_
		//-------------------------------------

		back->Draw();

		//
		XMMATRIX blockScaleMatrix =//�g�� �X�P�[�����O
			XMMatrixScaling(1, 1, 1);
		XMMATRIX blockTransMatrix= //�ړ� �}�g���N�X
			XMMatrixTranslation(0, 0.5f, 0);//�������
			
		XMMATRIX blockWorldMatrix =
			blockScaleMatrix *
			blockTransMatrix;
				
		//�]�u�s��@�萔�o�b�t�@�ɐݒ�
		consBufferMatrix.world = XMMatrixTranspose(
			blockWorldMatrix);
		
		//new char[1];
		//GPU�ɒ萔�o�b�t�@�iMatrix)��]��
		g_DX11Manager.UpdateConstantBuffer(
			cbuffer.Get(), consBufferMatrix);

						
		BlockModel.Draw();

		XMVECTOR beforePos = player->GetPos();

		XMFLOAT3 befpos;//(x,y,z) �O�̈ʒu

		XMStoreFloat3(&befpos, beforePos);//�s���float x,y,z�ɕϊ�
	/*	befpos.x = beforePos.m128_f32[0];
		befpos.y = beforePos.m128_f32[1];
		befpos.z = beforePos.m128_f32[2];*/
		//unitychan�̍s�Ɨ�������Ă݂�
		//(0,0)�Ȃ�΁A�q�b�g
		//(0,0)�̏��Ƀu���b�N������Ƃ����O��
		int before_row = (int)(befpos.z / 1.0f);//�s �c ��v���X
		int before_col = (int)(befpos.x / 1.0f);//�� �� �E�v���X


		//unitychan �X�V�i����A�W�����v�A�A�j���[�V�����j-----------------------------------------
		player->PlayerUpdate();
		//-----------------------------------------------------------------------------------------


		XMVECTOR nowPos = player->GetPos();

		XMFLOAT3 nowfpos;//(x,y,z) ���݂̈ʒu

		XMStoreFloat3(&nowfpos, nowPos);//�s���float x,y,z�ɕϊ�

		//unitychan�̍s�Ɨ�������Ă݂�
		//(0,0)�Ȃ�΁A�q�b�g
		//(0,0)�̏��Ƀu���b�N������Ƃ����O��
		int now_row = (int)(nowfpos.z / 1.0f);//�s �c ��v���X
		int now_col = (int)(nowfpos.x / 1.0f);//�� �� �E�v���X

		//�q�b�g����
		if (now_row == 0 && now_col == 0) {

			//Unity����񂪃u���b�N�ɓ�������
			//���̈ʒu�ɖ߂� �߂荞�ݏC��
			nowfpos.x = befpos.x;
			nowfpos.z = befpos.z;

			nowPos = XMLoadFloat3(&nowfpos);

			player->SetPos(nowPos);



		}



		//bool PlayerHit(XMFLOAT3 p_pos, XMFLOAT3 b_pos, float p_len, float b_len); //Box�Ƃ̓����蔻�� 

		player->PlayerAnimation();
		player->PlayerJump();

		//unitychan �`��
		player->PlayerDraw();

		//---------------------------------
		// �t�H���g��`��
		//---------------------------------
		FLOAT x = 500.0f, y = 50.0f;
		TCHAR tmp[32] = "Unitychan Model";
		pFont->DrawAnkText(g_DX11Manager.m_pImContext.Get(), tmp,
			XMFLOAT4(0.2f, 0.5f, 1.0f, 0.75f), x, y);
		//---------------------------------
		// UI�̕`��
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
		// Stage �̕`��@End
		//---------------------------------
		g_DX11Manager.DrawEnd();
		
	}

	//mciSendString("close backmusic", NULL, 0, NULL);
	//-----------------------------------------
	// ��������� Start
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
	// ��������� End
	//-----------------------------------------


	return msg.message;
	
}