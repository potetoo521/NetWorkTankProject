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

	//�Ǘ��p�v���C���[�f�[�^
	Player_Data p;

	//���M�f�[�^
	SEND_SERVER_DATA s_send;

	//�l�b�g���[�N�֌W
	IPDATA IP;
	int port = 26;//�g�p�|�[�g


	//�ڑ��ҋ@��Ԃɂ���
	PreparationListenNetWork(port);

	//�T�u�X���b�hNo1
	thread* p1 = new thread([&]() {
		int DataLenght = -1;//��M�f�[�^�̃T�C�Y�p
		unsigned char scene = CONNECTING;

		//����ڑ��ҋ@
		while (scene==CONNECTING) {
			if (CheckHitKey(KEY_INPUT_ESCAPE)) scene = -1;

			p.NetHandle[T1] = GetNewAcceptNetWork();
			if (p.NetHandle[T1] != -1) {
				char ID[4];
				sprintf_s(ID, "%d", T1);
				NetWorkSend(p.NetHandle[T1], &ID, sizeof(ID));//ID�𑗐M
				GetNetWorkIP(p.NetHandle[T1], &p.IP[T1]);//IP�A�h���X�擾
				p.flg[T1] = 1;//�t���O���X�V
				scene = ONLINE;
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//�T�u���C�����[�v
		while (scene==ONLINE) {
			if (CheckHitKey(KEY_INPUT_ESCAPE) || p.NetHandle[T1] == -1) scene = -1;

			DataLenght = GetNetWorkDataLength(p.NetHandle[T1]);//�f�[�^��M�̗L��
			if (DataLenght != 0) {
				char str[256] = { "null" };//��M�f�[�^�ۑ��p
				SEND_CLIENT_DATA c_send;//�N���C�A���g����̑��M�f�[�^
				//�f�[�^��M����
				NetWorkRecv(p.NetHandle[T1], str, sizeof(SEND_CLIENT_DATA));
				memcpy_s(&c_send, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));

				//���M�f�[�^�̍X�V

				//�v���C���[�f�[�^�̍X�V
				p.p_data[T1].pos = c_send.pos[T1];				//�ʒu���X�V

				//�e�ۂƂ̓����蔻�����
				




				//�e�̏���
				//�e�̈ړ��x�N�g�����[�����ᖳ���ꍇ
				if (c_send.m_vec.x != 0.0f || c_send.m_vec.y != 0.0f) {
					//���M����e�̈ړ��x�N�g���̏����X�V
					p.tama_vec[T1] = c_send.m_vec;
				}
			}
			if (ProcessMessage() == -1) break;
		}
	});
	
	thread* p2 = new thread([&]() {
		int DataLenght = -1;//��M�f�[�^�̃T�C�Y�p
		unsigned char scene = CONNECTING;

		//����ڑ��ҋ@
		while (scene==CONNECTING) {
			if (CheckHitKey(KEY_INPUT_ESCAPE)) scene = -1;

			p.NetHandle[T2] = GetNewAcceptNetWork();
			if (p.NetHandle[T2] != -1) {
				char ID[4];
				sprintf_s(ID, "%d", T2);
				NetWorkSend(p.NetHandle[T2], &ID, sizeof(ID));//ID�𑗐M
				GetNetWorkIP(p.NetHandle[T2], &p.IP[T2]);//IP�A�h���X�擾
				p.flg[T2] = 1;//�t���O���X�V
				scene = ONLINE;
				break;
			}
			if (ProcessMessage() == -1)break;
		}

		//�T�u���C�����[�v
		while (scene==ONLINE) {
			if (CheckHitKey(KEY_INPUT_ESCAPE) || p.NetHandle[T2] == -1) scene = -1;

			DataLenght = GetNetWorkDataLength(p.NetHandle[T2]);//�f�[�^��M�̗L��
			if (DataLenght != 0) {
				char str[256] = { "null" };//��M�f�[�^�ۑ��p
				SEND_CLIENT_DATA c_send;//�N���C�A���g����̑��M�f�[�^
				//�f�[�^��M����
				NetWorkRecv(p.NetHandle[T2], str, sizeof(SEND_CLIENT_DATA));
				memcpy_s(&c_send, sizeof(SEND_CLIENT_DATA), str, sizeof(SEND_CLIENT_DATA));

				//�v���C���[�f�[�^�̍X�V
				//�ʒu���X�V
				p.p_data[T2].pos = c_send.pos[T2];

				//���M�f�[�^�̍X�V
				//�e�̈ړ��x�N�g���̏���
				//�e�̈ړ��x�N�g�����[�����ᖳ���ꍇ
				if (c_send.m_vec.x != 0.0f || c_send.m_vec.y != 0.0f) {
					//���M����e�̈ړ��x�N�g���̏����X�V
					p.tama_vec[T2] = c_send.m_vec;
				}
			}
			if (ProcessMessage() == -1) break;
		}
	});

	//���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		//�N���[����IP�A�h���X
		GetMyIPAddress(&IP, 1, NULL);

		//��
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"PC��IP�A�h���X:%d.%d.%d.%d  �ڑ��|�[�g %d size:%d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			port,
			sizeof(Player_Data)
		);

		//�v���C���[
		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"NetHandle:%d IP�A�h���X:%d.%d.%d.%d�@x=%4f,y=%4f flg=%d ",
				p.NetHandle[i],
				p.IP[i].d1,
				p.IP[i].d2,
				p.IP[i].d3,
				p.IP[i].d4,
				p.p_data[i].pos.x,
				p.p_data[i].pos.y,
				p.flg[i]
			);
		}

		//�ؒf�����ꍇ
		int LostHandle = GetLostNetWork();
		//�ؒf�����v���C���[�̃f�[�^��������
		for (int i = 0; i < MAX; i++) {
			if (LostHandle == p.NetHandle[i]) {
				p.NetHandle[i] = -1;
				p.IP[i] = { 0,0,0,0 };
				p.p_data[i].pos = { -1.0f,-1.0f };
				p.flg[i] = -1;
			}
		}

		//�f�[�^�̑��M
		for (int i = 0; i < MAX; i++) {
			if (p.NetHandle[i] != -1) {
				NetWorkSend(p.NetHandle[i], &p, sizeof(Player_Data));
			}
		}

		//�e�̈ړ��x�N�g����������
		for (int i = 0; i < MAX; i++) {
			p.tama_vec[i] = { 0.0f,0.0f };
		}

		ScreenFlip();
		if (ProcessMessage() == -1)break;
	}
	p1->join();
	p2->join();
	delete p1;
	delete p2;

	DxLib_End();
	return 0;
}