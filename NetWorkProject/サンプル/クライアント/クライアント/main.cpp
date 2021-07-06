#pragma once
#include "main.h"
#include "chara.h"
#include "mouse.h"
#include "net.h"
#include <thread>
#include <iostream>

//���X�g(�e�p�j
list<unique_ptr<Bace>> bace;

//�N���C�A���g�p�v���O����(TCP/IP)
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
	SetWindowText("�N���C�A���g:�|�[�g27");

	//�v���C���[�I�u�W�F�N�g�̐���
	Player* player[MAX];
	for (int i = 0; i < MAX; i++) {
		player[i]= new Player();
	}
	//�}�E�X�J�[�\��
	Mouse* mouse = new Mouse();

	//���̃v���C���[
	Player_Data o_p;
	for (int i = 0; i < MAX; i++) {
		o_p.p_data[i] = new Player();
	}

	//�v���C���[�̈ʒu���
	Player_Point all_p_pos;
	for (int i = 0; i < MAX; i++) {
		all_p_pos.pos[i].x = 0.0f;
		all_p_pos.pos[i].y = 0.0f;
	}

	//�l�b�g���[�N�֌W
	IPDATA IP;//IP�A�h���X
	int NetHandle;//�l�b�g���[�N�n���h��
	int port = 26;//�|�[�g

	//IP�A�h���X�Z�b�g
	IP = IP_set();

	//�T�[�o�[�ŊǗ����Ă���ID(�X���b�hNo�j
	int server_ID{ -1 };

	//�ڑ�����
	NetHandle = ConnectNetWork(IP, port);


	//����ڑ�
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//��ʃN���A
		if (NetHandle != -1) {
			//�ڑ�����
			//�T�[�o�[����̉����ҋ@
			while (!ProcessMessage()) {
				//����M�f�[�^�𒲂ׂ�
				if (GetNetWorkDataLength(NetHandle) != 0) {
					char str[] = "null";
					//�f�[�^�̎�M
					NetWorkRecv(NetHandle, str, sizeof(server_ID));
					//�o�^ID�̎擾
					server_ID=atoi(str);
					player[server_ID] = new Player(100.0f,100.0f);
					break;
				}
			}
			DrawString(0, 16, "�ڑ������B�����L�[�������Ă��������B",
				GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
		else {
			//�ڑ���
			DrawString(0, 0, "�ڑ����s", GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
	}

	//���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();
		
		//�f�[�^����M�����ꍇ
		if (GetNetWorkDataLength(NetHandle) != 0) {
			char str[256] = { "null" };//�f�[�^��M�p�o�b�t�@

			Player_Point send_all_p_pos;//��M�f�[�^�ꎞ�ۑ��p

			NetWorkRecv(NetHandle, str, sizeof(Player_Point));
			memcpy_s(&send_all_p_pos, sizeof(Player_Point), str, sizeof(Player_Point));

			//���̃v���C���[�̏���
			for (int i = 0; i < MAX; i++) {
				//ID�Ɣz��̓Y���������āA�����ȊO�̃I�u�W�F�N�g������
				if (i != server_ID) {
					//���v���C���[�̐V�K�ڑ�
					if (send_all_p_pos.flg[i] != all_p_pos.flg[i]) {
						//���v���C���[�̍쐬
						player[i] = new Player(0, 0);
						//�t���O�X�V
						all_p_pos.flg[i] = send_all_p_pos.flg[i];
					}
					player[i]->pos.x = all_p_pos.pos[i].x;
					player[i]->pos.y = all_p_pos.pos[i].y;
				}
			}
			//NetWorkRecv(NetHandle, str, sizeof(Player_Data));
			//memcpy_s(&o_p, sizeof(Player_Data), str, sizeof(Player_Data));
		}

		//����
		for (auto i = bace.begin(); i != bace.end(); i++)
			(*i)->Action(bace);//���X�g�̏����i�e�j

		//�v���C���[�ƃ}�E�X�̏��� ��������������f�[�^�𑗐M
		//player[server_ID]->Action(bace);
		if (mouse->Action(bace, player[server_ID]->pos.x, player[server_ID]->pos.y) || player[server_ID]->Action(bace)){
			//���M�f�[�^�̍쐬
			SEND_CLIENT_DATA send;
			send.p_vec = player[server_ID]->vec;
			send.m_vec = mouse->b_v;
			NetWorkSend(NetHandle, &send, sizeof(send));
		}
	

		//�`��
		//�e
		for (auto i = bace.begin(); i != bace.end(); i++)  (*i)->Draw();

		//�v���C���[
		player[server_ID]->Draw();

		//�}�E�X�J�[�\��
		mouse->Draw();

		//���X�g����s�v�I�u�W�F�N�g���폜�i�e�j
		for (auto i = bace.begin(); i != bace.end(); i++) {
			if ((*i)->ID == -1) {
				i = bace.erase(i);
				break;
			}
		}

		//�l�b�g�n���h��
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"NetHandle:%d",
			NetHandle
		);

		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"x=%4f,y=%4f\nvx=%4f,vy=%4fA",
				all_p_pos.pos[i].x,
				all_p_pos.pos[i].y
			);
		}
		/*
		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0,i*16+32,GetColor(255,255,255),
				"NetHandle:%d IP�A�h���X:%d.%d.%d.%d�@x=%4f,y=%4f",
				o_p.NetHandle[i],
				o_p.IP[i].d1,
				o_p.IP[i].d2,
				o_p.IP[i].d3,
				o_p.IP[i].d4,
				o_p.p_data[i]->pos.x,
				o_p.p_data[i]->pos.y
			);
		}
		*/
		ScreenFlip();
		if (ProcessMessage() == -1) break;
	}

	//�l�b�g���[�N�̐ؒf
	CloseNetWork(NetHandle);

	DxLib_End();

	return 0;
}