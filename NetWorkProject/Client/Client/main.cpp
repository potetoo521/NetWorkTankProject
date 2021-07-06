//�}���`�X���b�hTCP�ʐM�@�N���C�A���g��
//Dx���C�u�����g�p
#pragma once
#include "character.h"

//#include "character.h"
#include <memory>
//���X�g
std::list<unique_ptr<Base>>datalist;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd) 
{
	//window���[�h�̐؂�ւ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode((int)WIDTH, (int)HEIGHT, 32);
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

	//char image_str[MAX][256];//�摜�ǂݍ���


	//�摜�̓ǂݍ���
	for (int i = 0; i < MAX; i++)
	{
		img[0] = LoadGraph("image/maid.png");
		img[1] = LoadGraph("image/Bullet.jpg");
	}
	
	//����M�f�[�^�����p
	char StrBuf[256] = { "null" };//256�o�C�g�܂�


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
	auto add = (unique_ptr<Base>) my_Data;
	datalist.emplace_back(move(add));//���X�g�ɒǉ�

	//�f�[�^���M�p�f�[�^
	Player* databox = new Player();

	//�S�Ẵv���C���[�f�[�^(���g���܂�)
	SendData* Player_ALL = new SendData();

	//Player* PlayerChar[MAX];//�v���C���[�f�[�^�ҏW�p
	//for (int i = 0; i < MAX; i++)//�e�X�g
	//{
	//	PlayerChar[i] = new Player();//�v���C���[�f�[�^�쐬
	//	auto addAll = (unique_ptr<Base>) PlayerChar[i];//�S�Ẵv���C���[�f�[�^�����X�g�ɒǉ�
	//	datalist.emplace_back(move(addAll));//���X�g�ɒǉ�
	//}
	//
	//
	
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

			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));//�f�[�^���󂯎��ϊ�

			DrawString(0, 16, "�ڑ������B�����L�[�������Ă��������B",
													GetColor(255, 255, 255));
			ScreenFlip();
			WaitKey();
			break;
		}
		else 
		{
			//�ڑ���
			DrawString(0, 0, "�ڑ��m�����E�E�E", GetColor(255, 255, 255));
		}
		ScreenFlip();
	}

	struct DataBox { //����M�p�\����(�e�X�g)
		Pos pos{ 0.0f,0.0f };    //�ʒu
		Vec vec{ 0.0f,0.0f };    //�ړ��x�N�g��
		Pos moupos{ 0, 0 };        //mouse�̈ʒu
		Vec mouvec{ 0,0 };       //mouse�x�N�g��
		GraphSize gr_size{ 0,0 };//�摜�T�C�Y

	};

	//���C�����[�v(Esc�L�[�ŏI��)
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//��ʃN���A


		//��M�f�[�^�����邩�`�F�b�N
		if (GetNetWorkDataLength(NetHandel) != 0) {
			//�f�[�^����M�����ꍇ
			NetWorkRecv(NetHandel, StrBuf, sizeof(SendData));
			//�v���C���[�S�̃f�[�^�̍X�V
			memcpy_s(Player_ALL, sizeof(SendData), StrBuf, sizeof(SendData));//�f�[�^���󂯎��

		}
		else
		{

			//�f�[�^����M���Ă��Ȃ��ꍇ
		    databox->vec    = my_Data->vec;  //�ړ� Vec��� 8

			//�e�ۂ̍쐬�������𑗂�Ƃ��̓x�N�g���ƈʒu���AID������ΕʃN���C�A���g���ō쐬�ł���
			databox->mouvec = my_Data->mouvec; //mousevec Vec��� 8

			my_Data->mouvec = { 0.0f,0.0f };//�x�N�g����������

			//�f�[�^���M
			NetWorkSend(NetHandel, &databox, sizeof(SendData)); //CharacterData���M
	
		}

		DrawFormatString(0, 256, GetColor(255, 255, 255),
			"mouse_x:%f         mouse_y:%f"    "pos_x:%f          pos_y:%f",
			my_Data->moupos.x,
			my_Data->moupos.y,
			my_Data->pos.x,
			my_Data->pos.y
		);


		//���X�g�̃��\�b�h�����s
		for (auto i = datalist.begin(); i != datalist.end(); i++) {

			(*i)->Action(datalist);//�S�ẴI�u�W�F�N�g��Action����
	
			Player* data = ((Player*)(*i).get());//�v���C���[�f�[�^

			if (IsVariable(data->mouvec))//�x�N�g�������݂��邩
			{
				//��M�f�[�^�����Ɋe�v���C���[�̃x�N�g���ƈʒu���Q�Ƃ��e�ۍ쐬(Test)
				Bullet* bullet = new Bullet(data->pos.x, data->pos.y, data->mouvec.x, data->mouvec.y, data->ID);//�ʒu�ƕ����x�N�g��
				auto add = (unique_ptr<Bullet>) bullet;
				datalist.emplace_back(move(add));//���X�g��bullet��ǉ�
			}
				
		}

		for (auto i = datalist.begin(); i != datalist.end(); i++) {

			(*i)->Draw();//�S�ẴI�u�W�F�N�g�̕`�揈��
	
		}

		//���X�g����v�f���폜(ID��-999�̎��ɍ폜)
		for (auto i = datalist.begin(); i != datalist.end(); i++)
		{
			if ((*i)->ID == DESTROY_ID)//ID��-999�Ȃ�delete
			{
				//���X�g����폜
				i = datalist.erase(i);
				break;
			}
		}

		/*
		//�`��
		//Player_ALL���g���ĉ�ʂ̍X�V
		for (int i = 0; i < MAX; i++) {
			if (Player_ALL->player[i].ID != -1) {//�v���C���[��ID���g�p�\��

				//Action���s
				if (IsVariable(Player_ALL->player[i].mouvec))//�l�������Ă��邩����
				{
					Player data = Player_ALL->player[i];//playerData�����ۑ�

					//��M�f�[�^�����Ɋe�v���C���[�̃x�N�g���ƈʒu���Q�Ƃ��e�ۍ쐬(Test)
					Bullet* bullet = new Bullet(data.pos.x, data.pos.y, data.mouvec.x, data.mouvec.y, data.ID);//�ʒu�ƕ����x�N�g��
					auto add = (unique_ptr<Bullet>) bullet;
					datalist.emplace_back(move(add));//���X�g��bullet��ǉ�
					
				}
				
				//�L����
				DrawGraphF(Player_ALL->player[i].pos.x,
					Player_ALL->player[i].pos.y,
					img[i],
					TRUE
				);
				//���O
				DrawStringF(Player_ALL->player[i].pos.x,
					Player_ALL->player[i].pos.y,
					Player_ALL->player[i].name,
					GetColor(255, 255, 255)
				);
			}
		}

		//DrawGraphF(0.0f, 0.0f, img[Player_ALL->data->ID], TRUE);//ID�\��
*/	
	

		ScreenFlip();//��ʍX�V

		//��O���������Ń��[�v�𔲂���
		if (ProcessMessage() == -1)break;
	}

	DxLib_End();//Dx���C�u�����̉��
	return 0;
}




