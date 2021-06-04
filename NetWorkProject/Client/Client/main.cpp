//�}���`�X���b�hTCP�ʐM�@�N���C�A���g��
//Dx���C�u�����g�p
#pragma once
#include "main.h"

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
	Data* my_Data = new Data(0.0f, 0.0f, name);

	//����ڑ�(�T�[�o�[�֐ڑ��j
	NetHandel = ConnectNetWork(IP, Port);//���͂���IP�Ɛݒ肵���|�[�g���g�p


	struct MousePos {
		int mouse_x, mouse_y;


	};

	MousePos mop{ 0,0 };


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

		bool net_Receive = false;

		//��M�f�[�^�����邩�`�F�b�N
		if (GetNetWorkDataLength(NetHandel) != 0) {
			//�f�[�^����M�����ꍇ
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));
			//�v���C���[�S�̃f�[�^�̍X�V
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));
			net_Receive = true;
		}

		//Pos mop{ 0.0f,0.0f };
		if(net_Receive==false)
		{
			//�f�[�^����M���Ă��Ȃ��ꍇ
			//�ړ�����
			Vec v{ 0.0f,0.0f };
			if (CheckHitKey(KEY_INPUT_UP)) v.y = -4.0f;
			if (CheckHitKey(KEY_INPUT_DOWN)) v.y = 4.0f;
			if (CheckHitKey(KEY_INPUT_LEFT)) v.x = -4.0f;
			if (CheckHitKey(KEY_INPUT_RIGHT)) v.x = 4.0f;
			//���͂��������ꍇ�Ƀf�[�^�𑗐M
			if (v.x != 0.0f || v.y != 0.0f) {
				//�f�[�^���M
				NetWorkSend(NetHandel, &v, sizeof(Vec));
			}

		
			//�e�۔��˖ڕW�擾����
			if (GetMouseInput()&MOUSE_INPUT_LEFT) {
				//�����ꂽ��
			
				//mouse�J�[�\���̈ʒu���Z�b�g
				GetMousePoint(&mop.mouse_x,&mop.mouse_y);


				//�f�[�^���M
				NetWorkSend(NetHandel, &mop, sizeof(Pos));

			}
			else {
				//������Ă��Ȃ�
			}

		}

		DrawFormatString(0, 16, GetColor(255, 255, 255),
			"mouse_x:%d          mouse_y:%d",
			mop.mouse_x,
			mop.mouse_y
		);


		//�`��
		//Player_ALL���g���ĉ�ʂ̍X�V
		for (int i = 0; i < MAX; i++) {
			if (Player_ALL->data[i].ID != -1) {
				//�L����
				DrawGraphF(Player_ALL->data[i].pos.x,
					Player_ALL->data[i].pos.y,
					img[i],
					TRUE
				);
				//���O
				DrawStringF(Player_ALL->data[i].pos.x,
					Player_ALL->data[i].pos.y,
					Player_ALL->data[i].name,
					GetColor(255, 255, 255)
				);
			}


		}
		DrawGraphF(0.0f, 0.0f, img[Player_ALL->data->ID], TRUE);
	
	

		ScreenFlip();//��ʍX�V

		//��O���������Ń��[�v�𔲂���
		if (ProcessMessage() == -1)break;
	}

	DxLib_End();//Dx���C�u�����̉��
	return 0;
}