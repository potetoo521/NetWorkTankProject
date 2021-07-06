#include "main.h"
#include "chara.h"
#include "net.h"//main��chara�̌�ɓǂݍ���
#include <thread>
#include <iostream>

//�T�[�o�[
int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE, _In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//window���[�h�ؑ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode(800, 600, 32);
	//�o�b�N�O���E���h�����̋���
	SetAlwaysRunFlag(TRUE);
	//���d�N���̋���
	SetDoubleStartValidFlag(TRUE);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	//�o�b�N�o�b�t�@���g���ݒ�
	SetDrawScreen(DX_SCREEN_BACK);

	SetWindowText("�T�[�o�[:�|�[�g26");

	//�Ǘ��p�v���C���[�f�[�^�i�\���́j
	Player_Data p;
	for (int i = 0; i < MAX; i++) {
		p.p_data[i] = new Player();
	}

	//�v���C���[�̈ʒu���
	Player_Point all_p_pos;
	for (int i = 0; i < MAX; i++) {
		all_p_pos.pos[i].x = 0.0f;
		all_p_pos.pos[i].y = 0.0f;
	}

	//�l�b�g���[�N�֌W
	IPDATA IP;
	int port = 26;//�g�p�|�[�g
	
	//�ڑ��ҋ@��Ԃɂ���
	PreparationListenNetWork(port);

	//�T�u�X���b�hNo1
	thread* p1 = new thread([&]() {
		IPDATA ip{ 0 };
		int DataLength = -1;
		char StrBuf[512]{ "null" };//����M�f�[�^�p
		SEND_CLIENT_DATA scData;
		
		//����ڑ��ҋ@
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			//GetNewAcceptNetWork()�Őڑ��̗L�����m�F
			p.NetHandle[T1] = GetNewAcceptNetWork();
			if( p.NetHandle[T1] != -1 ){
				char text[sizeof(int)];
				sprintf_s(text, "%d", T1);
				NetWorkSend(p.NetHandle[T1], &text, sizeof(int));//ID�̑��M
				GetNetWorkIP(p.NetHandle[T1], &p.IP[T1]);//IP�A�h���X�擾
				all_p_pos.flg[T1] = { 1 };
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//�T�u���C�����[�v
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			if (p.NetHandle[T1] != -1) {
				DataLength = GetNetWorkDataLength(p.NetHandle[T1]);
				if (DataLength != 0) {
					char str[256] = { "null" };
					//�f�[�^��M
					NetWorkRecv(p.NetHandle[T1], str, sizeof(SEND_CLIENT_DATA));
					memcpy_s(&scData, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));
					//�v���C���[�̈ʒu�X�V
					p.p_data[T1]->pos.x = p.p_data[T1]->pos.x + scData.p_vec.x;
					p.p_data[T1]->pos.y = p.p_data[T1]->pos.y + scData.p_vec.y;

					//�ʒu���
					all_p_pos.pos[T1].x = p.p_data[T1]->pos.x;
					all_p_pos.pos[T1].y = p.p_data[T1]->pos.y;
					//�e�ړ��x�N�g��
					all_p_pos.m_vec[T1].x = scData.m_vec.x;
					all_p_pos.m_vec[T1].x = scData.m_vec.x;
				}

				//�f�[�^�̑��M
				if (CheckHitKey(KEY_INPUT_SPACE)) {
					NetWorkSend(p.NetHandle[T1], &all_p_pos, sizeof(Player_Point));
				}
			}
			if (ProcessMessage() == -1)break;
		}
	});

	/*
	thread* p2 = new thread([&]() {
		IPDATA ip{ 0 };
		int DataLength = -1;
		char StrBuf[512]{ "null" };//����M�f�[�^�p
		SEND_CLIENT_DATA scData;

		//����ڑ��ҋ@
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			//GetNewAcceptNetWork()�Őڑ��̗L�����m�F
			p.NetHandle[T2] = GetNewAcceptNetWork();
			if( p.NetHandle[T2] != -1 ){
				char text[sizeof(int)];
				sprintf_s(text, "%d", T2);
				NetWorkSend(p.NetHandle[T2], &text, sizeof(int));//ID�̑��M
				GetNetWorkIP(p.NetHandle[T2], &p.IP[T1]);//IP�A�h���X�擾
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//�T�u���C�����[�v
		while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
			if (p.NetHandle[T2] != -1) {
				DataLength = GetNetWorkDataLength(p.NetHandle[T2]);
				if (DataLength != 0) {
					char str[256] = { "null" };
					//�f�[�^��M
					NetWorkRecv(p.NetHandle[T2], str, sizeof(SEND_CLIENT_DATA));
					memcpy_s(&scData, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));
					//�v���C���[�̈ʒu�X�V
					p.p_data[T2]->pos.x = p.p_data[T2]->pos.x + scData.p_vec.x;
					p.p_data[T2]->pos.y = p.p_data[T2]->pos.y + scData.p_vec.y;

					//�ʒu���
					all_p_pos.pos[T2].x = p.p_data[T2]->pos.x;
					all_p_pos.pos[T2].y = p.p_data[T2]->pos.y;
					//�e�ړ��x�N�g��
					all_p_pos.m_vec[T2].x = scData.m_vec.x;
					all_p_pos.m_vec[T2].x = scData.m_vec.x;
				}

				//�f�[�^�̑��M
				if (CheckHitKey(KEY_INPUT_SPACE)) {
					NetWorkSend(p.NetHandle[T2], &all_p_pos, sizeof(Player_Point));
				}
			}
			if (ProcessMessage() == -1)break;
		}
	});
	*/

	//���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		//�N���[����IP�A�h���X
		GetMyIPAddress(&IP, 1, NULL);

		//��
		DrawFormatString(0,0,GetColor(255,255,255),
			"PC��IP�A�h���X:%d.%d.%d.%d  �ڑ��|�[�g %d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			port
		);

		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"NetHandle:%d IP�A�h���X:%d.%d.%d.%d�@x=%4f,y=%4f",
				p.NetHandle[i],
				p.IP[i].d1,
				p.IP[i].d2,
				p.IP[i].d3,
				p.IP[i].d4,
				p.p_data[i]->pos.x,
				p.p_data[i]->pos.y
				);
		}

		//�ؒf�����ꍇ�̏���
		int LostHandle = GetLostNetWork();
		for (int i = 0; i < MAX; i++) {
			//�f�[�^�̑��M
			if (p.NetHandle[i] != -1) {
				//�l�b�g���[�N�n���h��������΁A�f�[�^�𑗐M
				NetWorkSend(p.NetHandle[i], &all_p_pos, sizeof(Player_Point));
			}

			//�ؒf�����v���C���[�̃f�[�^��������
			if (LostHandle == p.NetHandle[i]) {
				p.NetHandle[i] = -1;
				p.IP->d1 = 0;
				p.IP->d2 = 0;
				p.IP->d3 = 0;
				p.IP->d4 = 0;
				p.p_data[i]->Init();
			}
		}

		ScreenFlip();
		if (ProcessMessage() == -1)break;
	}
	p1->join();
	//p2->join();
	delete p1;
	//delete p2;

	DxLib_End();
	return 0;
}