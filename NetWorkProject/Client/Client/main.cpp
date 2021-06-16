//�}���`�X���b�hTCP�ʐM�@�N���C�A���g��
//Dx���C�u�����g�p
#pragma once
#include "main.h"
#include "character.h"
#include <memory>
//���X�g
std::list<unique_ptr<Base>>base;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd) 
{
	//window���[�h�̐؂�ւ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode(WIDTH, HEIGHT, 32);
	//�o�b�N�O���E���h�����̋���
	SetAlwaysRunFlag(TRUE);
	//���d�N���̋���
	SetDoubleStartValidFlag(TRUE);
	//Dx���C�u�����̏�����
	if (DxLib_Init() == -1) return -1;//���s������v���O�����I��

	//�o�b�N�o�b�t�@���g���ݒ�
	SetDrawScreen(DX_SCREEN_BACK);
	//winodow�̖��O
	SetWindowText("�N���C�A���g");

	int img[MAX];

	char image_str[MAX][256];//�摜�ǂݍ���


	//�摜�̓ǂݍ���
	for (int i = 0; i < MAX; i++)
	{
		img[0] = LoadGraph("image/maid.png");
		img[1] = LoadGraph("image/koiking.png");
		img[2] = LoadGraph("image/koiking.png");
		img[3] = LoadGraph("image/hitogage.png");

	}
	
	//����M�f�[�^�����p
	char StrBuf[256] = { "null" };//256�o�C�g�܂�

	//�S�Ẵv���C���[�f�[�^
	SendData* Player_ALL = new SendData();

	//�ʐM�֌W
	IPDATA IP;
	//�ʐM�p�̃n���h��
	int NetHandel;
	//�|�[�g
	int Port = 26;
	//�ʐM���IP�A�h���X�̐ݒ�
	IP = IP_set();

	//�v���C���f�[�^�쐬
	//���O�̓���
	char name[8] = "null";
	ClearDrawScreen();//��ʃN���A
	DrawString(0, 0, "���O����́@������8����/�S�p4�����܂�",
		GetColor(255, 255, 255));
	KeyInputString(0, 16, 10, name, FALSE);

	//���񑗐M�f�[�^�̍쐬
	Player* my_Data = new Player(0.0f, 0.0f, name);

	auto a = (unique_ptr<Base>) my_Data;
	base.push_back(move(a));


	//����ڑ�(�T�[�o�[�֐ڑ��j
	NetHandel = ConnectNetWork(IP, Port);//���͂���IP�Ɛݒ肵���|�[�g���g�p


	//�ڑ�����܂őҋ@
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//��ʃN���A

		if (NetHandel != -1) {
			//�ڑ�����
			//�T�[�o�[�Ƀf�[�^�𑗐M(���O�������M)
			NetWorkSend(NetHandel, &my_Data->name, sizeof(my_Data->name));
			//�T�[�o�[����̉����ҋ@
			while (!ProcessMessage()) {
				//����M�f�[�^�𒲂ׂ�
				if (GetNetWorkDataLength(NetHandel) != 0) break;
			}
			//��M�f�[�^��ϊ�
			//��M�f�[�^������������StrBuf�ɃR�s�[���āASendData�ɕϊ�
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));//�R�s�[
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));//�ϊ�

			DrawString(0, 16, "�ڑ������B�����L�[�������Ă��������B",
													GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
		else {
			//�ڑ���
			DrawString(0, 0, "�ڑ��m�����E�E�E", GetColor(255, 255, 255));
		}
		ScreenFlip();
	}

	//���C�����[�v(Esc�L�[�ŏI��)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//��ʃN���A

		bool net_Receive = false;//��M�f�[�^�����邩(Debug�p)

		//��M�f�[�^�����邩�`�F�b�N
		if (GetNetWorkDataLength(NetHandel) != 0) {
			//�f�[�^����M�����ꍇ
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));
			//�v���C���[�S�̃f�[�^�̍X�V
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));
			net_Receive = true;
		}
		else
		{
			//�f�[�^����M���Ă��Ȃ��ꍇ
			
			//�ړ�����
			Vec v{ 0.0f,0.0f };
			MousePos m{ 0,0 };
			bool f = false;

		     v = my_Data->vec;
			 m = my_Data->moupos;
			 f = my_Data->mouset_f;
			//�f�[�^���M
			NetWorkSend(NetHandel, &v, sizeof(Vec)); //character�ړ�Vec
	
			NetWorkSend(NetHandel, &m, sizeof(MousePos)); //Mouse�ʒu����Vec

			NetWorkSend(NetHandel, &f, sizeof(Pos)); //

		}

		DrawFormatString(0, 16, GetColor(255, 255, 255),
			"mouse_x:%d          mouse_y:%d"    "pos_x:%d          pos_y:%d",
			my_Data->moupos.x,
			my_Data->moupos.y,
			my_Data->pos.x,
			my_Data->pos.y
		);

		//Player���s
		my_Data->Action();//Action���s
		my_Data->Draw();//�`����s

		////���X�g�̃��\�b�h�����s
		//for (auto i = base.begin(); i != base.end(); i++) {
		//	(*i)->Action();//�S�ẴI�u�W�F�N�g�̏���
		//	
		//}
		//for (auto i = base.begin(); i != base.end(); i++) {
		//	(*i)->Draw();//�S�ẴI�u�W�F�N�g�̕`�揈��
		//
		//}

		//���X�g����v�f���폜(ID��-999�̎��ɍ폜)
		for (auto i = base.begin(); i != base.end(); i++)
		{
			if ((*i)->ID == DESTROY_ID)//ID��-999�Ȃ�delete
			{
				//���X�g����폜
				i = base.erase(i);
				break;
			}
		}

		//�`��
		//Player_ALL���g���ĉ�ʂ̍X�V
		for (int i = 0; i < MAX; i++) {
			if (Player_ALL->data[i].ID != -1) {
				//�L����
				/*DrawGraphF(Player_ALL->data[i].pos.x,
					Player_ALL->data[i].pos.y,
					img[i],
					TRUE
				);*/
				//���O
				DrawStringF(Player_ALL->data[i].pos.x,
					Player_ALL->data[i].pos.y,
					Player_ALL->data[i].name,
					GetColor(255, 255, 255)
				);
			}
		}

		//DrawGraphF(0.0f, 0.0f, img[Player_ALL->data->ID], TRUE);//ID�\��
	
	

		ScreenFlip();//��ʍX�V

		//��O���������Ń��[�v�𔲂���
		if (ProcessMessage() == -1)break;
	}

	DxLib_End();//Dx���C�u�����̉��
	return 0;
}