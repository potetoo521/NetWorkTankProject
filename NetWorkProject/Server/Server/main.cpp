//�}���`�X���b�hTCP�ʐM
//�T�[�o�[
//Dx���C�u�����g�p
#pragma once
#include "main.h"
#include <thread>
#include <iostream>
#include <list>
#include <memory>

//std::list<Data*>datalist;
list<unique_ptr<Base>>datalist;//�S�Ă�Actor���i�[�����

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//window���[�h�ؑ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode(WIDTH, HEIGHT, 32);
	//�o�b�N�O���E���h�����̋���
	SetAlwaysRunFlag(TRUE);
	//���d�N���̋���
	SetDoubleStartValidFlag(TRUE);

	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;

	//window�̖��O
	SetWindowText("�T�[�o�[");

	//�o�b�N�o�b�t�@���g�p
	SetDrawScreen(DX_SCREEN_BACK);

	//����M�f�[�^�����p
	char StrBuf[256] = { "NULL" };

	//�v���C���[�f�[�^
	Player* p_data[MAX];


	for (int i = 0; i < MAX; i++) p_data[i] = new Player();

	//���M�p�f�[�^
	SendData* Send_Data = new SendData();//�S�Ẵv���C���[��񂪓���

	//�l�b�g���[�N�֌W
	IPDATA IP;
	int Port = 26;
	int NetHandle[4] = { 0 };

	//////////////////////////////////////////////////

	//�ڑ��ҋ@��Ԃɂ���
	PreparationListenNetWork(Port);

	//�T�u�X���b�h
	thread* player[MAX];
	/*
	for (int i = 0; i < MAX; i++)
	{
		player[i] = new thread([&]() {

			IPDATA ip{ 0,0,0,0 };//IP�A�h���X
			int DataLength = -1;//��M�f�[�^�̑傫���擾�p
			int p1_NetHandle = -1;//�l�b�g���[�N�n���h��
			char StrBuf[256]{ "null" };//����M�f�[�^�p

			//����ڑ�����
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				p1_NetHandle = GetNewAcceptNetWork();//�l�b�g���[�N�n���h���擾
				if (p1_NetHandle != -1) {
					NetHandle[i] = p1_NetHandle;
					break;
				}
			}

			//�T�u�X���b�h�̃��C�����[�v
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				DataLength = GetNetWorkDataLength(p1_NetHandle);
				if (DataLength != 0) {
					//��M�f�[�^��StrBuf�Ɏ擾
					NetWorkRecv(p1_NetHandle, StrBuf, DataLength);
					//�ڑ����Ă����}�V����IP�A�h���X���擾
					GetNetWorkIP(p1_NetHandle, &ip);

					//IP�A�h���X���珉��̐ڑ����m�F
					if (p_data[i]->ip.d1 == ip.d1 && p_data[i]->ip.d2 == ip.d2 &&
						p_data[i]->ip.d3 == ip.d3 && p_data[i]->ip.d4 == ip.d4
						) {

						//���ڈȍ~�̐ڑ�s
						SendData player;//�ړ��x�N�g��
						MousePos mop{ 0,0 };   //mouse�ʒu
						bool mou_l;//���N���b�N�̏��

						//��M�f�[�^��ϊ�
						memcpy_s(&player, sizeof(SendData), StrBuf, sizeof(SendData));
						
						//�ړ�����
						p_data[i]->pos.x += player.data->pos.x;
						p_data[i]->pos.y += player.data->pos.y;
						/*
						//�}�E�X���N���b�N����Ă��邩
						if (mou_l==true)
						{
							p_data[0]->moupos.x = mop.x;
							p_data[0]->moupos.y = mop.y;


						}


						//�e�۔��ˏ���---
						if (mou_l) {//mouse���N���b�N���ꂽ�Ƃ��^

							//Player�̈ʒu���擾
							float p_x = p_data[0]->pos.x;
							float p_y = p_data[0]->pos.y;


							//�e�ۃX�|�[������
							auto a = (unique_ptr<Base>)new BulletData();
							datalist.push_back(move(a));

						}
						//�����蔻��
						for (auto i = datalist.begin(); i != datalist.end(); i++) {
							if ((*i)->ID == 1) {
								Pos e_pos = ((BulletData*)(*i).get())->pos;
								if (1) {

									;
								}
							}
						}

						//HP�̎c������

						//���M�f�[�^�̍X�V
						Send_Data->data[i].pos.x = p_data[i]->pos.x;
						Send_Data->data[i].pos.y = p_data[i]->pos.y;
						//���M�f�[�^�̍X�V
						Send_Data->data[i].moupos.x = p_data[i]->moupos.x;
						Send_Data->data[i].moupos.y = p_data[i]->moupos.y;



					}
					else {
						//����̐ڑ�
						//IP�Ɩ��O��o�^
						p_data[i]->ip = ip;
						p_data[i]->ID = 0;
						memcpy_s(p_data[i]->name, sizeof(p_data[i]->name),
							StrBuf, sizeof(p_data[i]->name));
						//���M�f�[�^�̍X�V
						strcpy_s(Send_Data->data[i].name, sizeof(p_data[i]->name), p_data[i]->name);

						Send_Data->data[i].pos = p_data[i]->pos;//�ʒu

						Send_Data->data[i].ip = p_data[i]->ip;//IP

						Send_Data->data[i].ID = p_data[i]->ID;//ID

						//�f�[�^�𑗐M
						NetWorkSend(p1_NetHandle, Send_Data, sizeof(SendData));
					}
				}
			}
			}
		);

*/

	struct DataBox { //����M�p�\����(�e�X�g)
		Pos pos;
		Vec vec;
		MousePos mou_p;
		bool bullet_f;
	};


		//p_data[0]==PlayerData
	thread* p1 = new thread([&]()
		{
			IPDATA ip{ 0,0,0,0 };//IP�A�h���X
			int DataLength = -1;//��M�f�[�^�̑傫���擾�p
			int p1_NetHandle = -1;//�l�b�g���[�N�n���h��
			char StrBuf[256]{ "null" };//����M�f�[�^�p

			//����ڑ�����
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				p1_NetHandle = GetNewAcceptNetWork();//�l�b�g���[�N�n���h���擾
				if (p1_NetHandle != -1) {
					NetHandle[0] = p1_NetHandle;
					break;
				}
			}

			//�T�u�X���b�h�̃��C�����[�v
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				DataLength = GetNetWorkDataLength(p1_NetHandle);
				if (DataLength != 0) {
					//��M�f�[�^��StrBuf�Ɏ擾
					NetWorkRecv(p1_NetHandle, StrBuf, DataLength);
					//�ڑ����Ă����}�V����IP�A�h���X���擾
					GetNetWorkIP(p1_NetHandle, &ip);

					//IP�A�h���X���珉��̐ڑ����m�F
					if (p_data[0]->ip.d1 == ip.d1 && p_data[0]->ip.d2 == ip.d2 &&
						p_data[0]->ip.d3 == ip.d3 && p_data[0]->ip.d4 == ip.d4
						) {

						//���ڈȍ~�̐ڑ�
						DataBox databox{0};//�g�p����f�[�^���i�[�p

						//��M�f�[�^��ϊ�
						memcpy_s(&databox, sizeof(DataBox), StrBuf, sizeof(DataBox));

						//�ړ�����
						p_data[0]->pos.x += databox.vec.x;
						p_data[0]->pos.y += databox.vec.y;

						if (databox.bullet_f==true)
						{
							p_data[0]->moupos.x = databox.mou_p.x;
							p_data[0]->moupos.y = databox.mou_p.y;
						}
						/*
						//�}�E�X���N���b�N����Ă��邩
						if (mou_l==true)
						{
							p_data[0]->moupos.x = mop.x;
							p_data[0]->moupos.y = mop.y;


						}


						//�e�۔��ˏ���---
						if (mou_l) {//mouse���N���b�N���ꂽ�Ƃ��^

							//Player�̈ʒu���擾
							float p_x = p_data[0]->pos.x;
							float p_y = p_data[0]->pos.y;


							//�e�ۃX�|�[������
							auto a = (unique_ptr<Base>)new BulletData();
							datalist.push_back(move(a));

						}
						//�����蔻��
						for (auto i = datalist.begin(); i != datalist.end(); i++) {
							if ((*i)->ID == 1) {
								Pos e_pos = ((BulletData*)(*i).get())->pos;
								if (1) {

									;
								}
							}
						}*/

						//HP�̎c������






						//���M�f�[�^�̍X�V
						Send_Data->data[0].pos.x = p_data[0]->pos.x;
						Send_Data->data[0].pos.y = p_data[0]->pos.y;
						//���M�f�[�^�̍X�V
						Send_Data->data[0].moupos.x = p_data[0]->moupos.x;
						Send_Data->data[0].moupos.y = p_data[0]->moupos.y;



					}
					else {
						//����̐ڑ�
						//IP�Ɩ��O��o�^
						p_data[0]->ip = ip;
						p_data[0]->ID = 0;
						memcpy_s(p_data[0]->name, sizeof(p_data[0]->name),
							StrBuf, sizeof(p_data[0]->name));
						//���M�f�[�^�̍X�V
						strcpy_s(Send_Data->data[0].name, sizeof(p_data[0]->name), p_data[0]->name);

						Send_Data->data[0].pos = p_data[0]->pos;//�ʒu

						Send_Data->data[0].ip = p_data[0]->ip;//IP

						Send_Data->data[0].ID = p_data[0]->ID;//ID

						//�f�[�^�𑗐M
						NetWorkSend(p1_NetHandle, Send_Data, sizeof(SendData));
					}
				}
			}
		}
	);

	//p_data[1]
	thread* p2 = new thread([&]()
		{
			IPDATA ip{ 0,0,0,0 };//IP�A�h���X
			int DataLength = -1;//��M�f�[�^�̑傫���擾�p
			int p2_NetHandle = -1;//�l�b�g���[�N�n���h��
			char StrBuf[256]{ "null" };//����M�f�[�^�p

			//����ڑ�����
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				p2_NetHandle = GetNewAcceptNetWork();//�l�b�g���[�N�n���h���擾
				if (p2_NetHandle != -1) {
					NetHandle[1] = p2_NetHandle;
					break;
				}
			}

			//�T�u�X���b�h�̃��C�����[�v
			while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
				DataLength = GetNetWorkDataLength(p2_NetHandle);
				if (DataLength != 0) {
					//��M�f�[�^��StrBuf�Ɏ擾
					NetWorkRecv(p2_NetHandle, StrBuf, DataLength);
					//�ڑ����Ă����}�V����IP�A�h���X���擾
					GetNetWorkIP(p2_NetHandle, &ip);

					//IP�A�h���X���珉��̐ڑ����m�F
					if (p_data[1]->ip.d1 == ip.d1 && p_data[1]->ip.d2 == ip.d2 &&
						p_data[1]->ip.d3 == ip.d3 && p_data[1]->ip.d4 == ip.d4
						) {
						//���ڈȍ~�̐ڑ�
						Vec v{ 0.0f,0.0f };
						//��M�f�[�^��ϊ�
						memcpy_s(&v, sizeof(Vec), StrBuf, sizeof(Vec));
						//�ړ�����
						p_data[1]->pos.x += v.x;
						p_data[1]->pos.y += v.y;

						//���M�f�[�^�̍X�V
						Send_Data->data[1].pos.x = p_data[1]->pos.x;
						Send_Data->data[1].pos.y = p_data[1]->pos.y;

					}
					else {
						//����̐ڑ�
						//IP�Ɩ��O��o�^
						p_data[1]->ip = ip;
						p_data[1]->ID = 1;
						memcpy_s(p_data[1]->name, sizeof(p_data[1]->name),
							StrBuf, sizeof(p_data[1]->name));
						//���M�f�[�^�̍X�V
						strcpy_s(Send_Data->data[1].name, sizeof(p_data[1]->name), p_data[1]->name);
						Send_Data->data[1].pos = p_data[1]->pos;//�ʒu
						Send_Data->data[1].ip = p_data[1]->ip;//IP
						Send_Data->data[1].ID = p_data[1]->ID;

						//�f�[�^�𑗐M
						NetWorkSend(p2_NetHandle, Send_Data, sizeof(SendData));
					}
				}
			}
		}
	);

	//p_da1ta[2]
	thread* p3 = new thread([&]() {});
	//p_data[3]
	thread* p4 = new thread([&]() {});

	//���C�����[�v(�T�[�o�[�Ǘ����)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//��ʃN���A

		//�N���[����IP�A�h���X
		GetMyIPAddress(&IP, 1, NULL);

		//�ؒf�󋵂��`�F�b�N
		int LostHandle = GetLostNetWork();

		for (int i = 0; i < MAX; i++) {

			//�f�[�^�𑗐M
			if (NetHandle[i] != -1) {
				NetWorkSend(NetHandle[i], Send_Data, sizeof(SendData));
			}

			//�ؒf�����v���C���[��������
			if (LostHandle == NetHandle[i]) {
				NetHandle[i] = 0;
				//�f�[�^�̏�����
				p_data[i]->Data_Init();
			}
		}

		//-------------------�󋵕\��--------------------------------
		DrawFormatString(0, 0, GetColor(255, 255, 255),
			"PC��IP�A�h���X:%d.%d.%d.%d �ڑ��|�[�g:%d",
			IP.d1,
			IP.d2,
			IP.d3,
			IP.d4,
			Port
		);

		for (int i = 0; i < MAX; i++)
		{
			//�v���C���[�󋵕\��
			DrawFormatString(0, i * 48 + 32, GetColor(255, 255, 255),
				"�X���b�h%d IP:%d.%d.%d.%d  name=%8s  x=%f:y=%f \n mou_x=%f;mou_y=%f",
				p_data[i]->ID,
				p_data[i]->ip.d1,
				p_data[i]->ip.d2,
				p_data[i]->ip.d3,
				p_data[i]->ip.d4,
				p_data[i]->name,
				p_data[i]->pos.x,
				p_data[i]->pos.y,
				p_data[i]->moupos.x,
				p_data[i]->moupos.y
			);
		}

		ScreenFlip();//��ʍX�V
		if ((ProcessMessage() == -1))break;
	}
		p1->join();
		p2->join();
		p3->join();
		p4->join();
		delete p1;
		delete p2;
		delete p3;
		delete p4;

		DxLib_End();
		return 0;
}









