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

	//�l�b�g���[�N�֌W
	IPDATA IP;//IP�A�h���X
	int NetHandle;//�l�b�g���[�N�n���h��
	int port = 26;//�|�[�g

	//IP�A�h���X�Z�b�g
	//IP = IP_set();
	IP.d1 = 172;
	IP.d2 = 17;
	IP.d3 = 80;
	IP.d4 = 103;

	//�T�[�o�[�ŊǗ����Ă���ID(�X���b�hNo�j
	int server_ID{ -1 };

	//�V�[��
	unsigned char scene = CONNECTING;

	//�v���C���[�f�[�^
	Player_Data p;

	//�v���C���[�I�u�W�F�N�g�̐���
	Player* player = new Player(0.0f, 0.0f);
	//�}�E�X�J�[�\��
	Mouse* mouse = new Mouse();

	//�ڑ�
	NetHandle = ConnectNetWork(IP, port);

	//�ڑ�
	while (scene==CONNECTING){
		if (CheckHitKey(KEY_INPUT_ESCAPE)) scene=-1;

		ClearDrawScreen();//��ʃN���A
		//�ڑ��ҋ@
		DrawString(0, 0, "�ڑ���",GetColor(255, 255, 255));
		if (NetHandle != -1) {
			//�f�[�^�������Ă����ꍇ
			if (GetNetWorkDataLength(NetHandle) != 0) {
				char str[4] = "";
				//�f�[�^�̎�M����
				if (NetWorkRecv(NetHandle, str, sizeof(4)) != -1){ 
					//�o�^ID�̎擾
					server_ID = atoi(str);
					p.flg[server_ID] = 1;//�Ǘ��f�[�^�̃t���O���X�V
					scene = ONLINE;//�V�[�����I�����C���ɐ؊�			
				}
			}
		}
		else {
			//�ڑ������s�����ꍇ�̏���
			DrawString(0, 16, "�ڑ����s", GetColor(255, 255, 255));
			WaitKey();
			scene = -1;
		}
		ScreenFlip();
	}

	NetWorkRecvBufferClear(NetHandle);//��M�f�[�^�o�b�t�@���N���A

	

	//���C�����[�v
	while (scene == ONLINE) {
		if (CheckHitKey(KEY_INPUT_ESCAPE)) scene = -1;

		ClearDrawScreen();
		int d_length = GetNetWorkDataLength(NetHandle);

		//�f�[�^����M�����ꍇ
		if (d_length >= sizeof(Player_Data)) {
			Player_Data r_recv;//��M�f�[�^�ۑ��p
			char str[sizeof(Player_Data)] = " ";
			NetWorkRecv(NetHandle, str, sizeof(Player_Data));
			memcpy_s(&r_recv, sizeof(Player_Data), str, sizeof(Player_Data));

			for (int i = 0; i < MAX; i++) {
				//�����ȊO��ID������
				if (server_ID != i) {

					//���݂̊Ǘ��t���O��-1�ŁA��M�����f�[�^��-1���ᖳ���ꍇ
					//�V�K�Őڑ������������ɂȂ�
					if (p.flg[i] == -1 && r_recv.flg[i] != -1) {
						//�V�K�ڑ����������ꍇ
						//���̃v���C���[��ǉ��ƍ쐬
						bace.emplace_back((unique_ptr<Bace>)new AnyPlayer(r_recv.flg[i]));
						p.flg[i] = r_recv.flg[i];//�t���O���X�V
					}

					//���̃v���C���[�̍��W���X�V
					if (p.flg[i] != -1) {
						for (auto a = bace.begin(); a != bace.end(); a++) {//���X�g
							if ((*a)->ID == p.flg[i]) {

								//����ID�̍��W���X�V
								((AnyPlayer*)(*a).get())->pos = r_recv.p_data[i].pos;
								//((AnyPlayer*)(*a).get())->FLAG = r_recv.p_data[i].hit_flag;//�q�b�g�t���O�X�V
								
								//((Player*)(*a).get())->FLAG = r_recv.p_data[i].hit_flag;

								//�U������
								//�����A�U���x�N�g����0.0f�ȊO��������e�𐶐����Ă��̕����ɔ�΂�
								if (r_recv.b_data[i].bullet_vec.x != 0.0f || r_recv.b_data[i].bullet_vec.y != 0.0f) {

									//�e��list�ɒǉ�
									bace.emplace_back((unique_ptr<Bace>)new Bullet(r_recv.b_data[i].bullet_vec.x, r_recv.b_data[i].bullet_vec.y,
										r_recv.p_data[i].pos.x, r_recv.p_data[i].pos.y, r_recv.p_data[i].ID));
								}
							}
						}
					}
				}
				//�v���C���[�Ǘ��f�[�^�̍��W�X�V
				p.p_data[i].pos = r_recv.p_data[i].pos;
			}
		}

		//�v���C���[�ƃ}�E�X(�U���j�ɓ�������������f�[�^�𑗐M
		if (mouse->Action(bace, player->pos.x, player->pos.y,player->ID) || player->Action(bace)) {
			//���M�f�[�^�̍쐬
			SEND_CLIENT_DATA send;
			send.pos[server_ID] = player->pos;//�ʒu���
			send.m_vec = mouse->b_v;//�e�̈ړ��x�N�g��
			NetWorkSend(NetHandle, &send, sizeof(send));//�f�[�^���M
		}

		//-----------------------------
		//for (auto i = bace.begin(); i != bace.end(); i++){ 
		// 
		//	if (((Bullet*)(*i).get())->ID == p.p_data->ID);
		// 
		// NetWorkSend(NetHandle,&send,sizeof(send));//�f�[�^���M
        //      	}
		//�q�b�g���肪�������e�ۂ�ID�Ɣ��˃v���C���[ID

		
		


		//-----------------------------
		

		//���X�g��Action����
		for (auto i = bace.begin(); i != bace.end(); i++) (*i)->Action(bace);

		//���X�g����s�v�I�u�W�F�N�g���폜
		for (auto i = bace.begin(); i != bace.end(); i++) {
			if ((*i)->FLAG == false) {
				i = bace.erase(i);
				break;
			}
		}

		//list�̕`��
		for (auto i = bace.begin(); i != bace.end(); i++)  (*i)->Draw();
		//�v���C���[
		player->Draw();
		//�}�E�X
		mouse->Draw();

		//�T�[�o�[��ID  �l�b�g�n���h��  ��M�f�[�^�T�C�Y
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"ID=%d NetHandle:%d DataLength=%d",
			server_ID,
			NetHandle,
			GetNetWorkDataLength(NetHandle)
		);

		//�v���C���[
		for (int i = 0; i < MAX; i++) {
			DrawFormatString(0, i * 16 + 32, GetColor(255, 255, 255),
				"IP�A�h���X:%d.%d.%d.%d�@x=%4f,y=%4f  flg=%d",
				p.IP[i].d1,
				p.IP[i].d2,
				p.IP[i].d3,
				p.IP[i].d4,
				p.p_data[i].pos.x,
				p.p_data[i].pos.y,
				p.flg[i]
			);
		}

		ScreenFlip();
		if (ProcessMessage() == -1) break;
	}

	//�l�b�g���[�N�̐ؒf
	CloseNetWork(NetHandle);

	DxLib_End();

	return 0;
}