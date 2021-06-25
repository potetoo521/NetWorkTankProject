//���X�g��
//DxLibrary�g�p
#pragma once
#include "main.h"
#include "character.h"
//#include <memory>//����������ɕK�v


//���j�[�N�|�C���^���g�������X�g
list<unique_ptr<Base>>base;

int APIENTRY wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE,
	_In_ LPWSTR lpCmdLine, _In_ int nShowCmd)
{
	//window���[�h�؂�ւ�
	ChangeWindowMode(TRUE);
	//window�T�C�Y
	SetGraphMode(WIDTH, HEIGHT, 32,FPS);

	//DxLibrary�̏�����
	if (DxLib_Init() == -1)return -1;

	//window�̖��O
	SetWindowText("�T���v��Game");

	//�o�b�N�o�b�t�@���g�p
	SetDrawScreen(DX_SCREEN_BACK);

	//���X�g�փv���C���[��ǉ�
	auto a = (unique_ptr<Base>)new Player();
	base.emplace_back(move(a));
	
	//auto a = (Base*)new Player();
	//base.push_back(a);


	//���C�����[�v
	while (CheckHitKey(KEY_INPUT_ESCAPE) == 0) {
		ClearDrawScreen();//��ʃN���A

		//���X�g�̃��\�b�h�����s
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Action(base);//�e�I�u�W�F�N�g�̏���
		
		for (auto i = base.begin(); i != base.end(); i++)
			(*i)->Draw();//�e�I�u�W�F�N�g�̕`�揈��

		//�I�u�W�F�N�g�̍폜
		for (auto i = base.begin(); i != base.end(); i++) {
			if (((Base*)(*i).get())->ID == Destroy_ID)
			{
				i = base.erase(i);   //�폜
				if (i == base.end())break;//���X�g�Ō���܂Ŋm�F
			}
		}

		//���X�g����v�f���폜(ID��-999�̎��ɍ폜)
		//for (auto i = base.begin(); i !=base.end() ; i++)
		//{
		//	if ((*i)->ID == -999)
		//	{
		//		//���X�g����폜
		//		delete(*i);
		//		i = base.erase(i);
		//		break;
		//	}
		//}

		//for (auto i = base.begin(); i != base.end(); i++)
		//{
		//	i = base.erase(i);
		//	break;
		//}

		ScreenFlip();//��ʍX�V
		//��O����
		if (ProcessMessage() == -1)break;


	}

	DxLib_End();

	return 0;
}

//�����蔻��
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel) {

	float magLen = (p_pixel + e_pixel)/2;

	float len = sqrtf((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));//���ς̒������擾
	
	if (len <= magLen)//MagLen == len�܂ł̋���
	{
		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
	}
	else
	{
		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
	}
};

//��ʂ̒[�ɗ������ʊO�ɏo�Ȃ��p�Ɉʒu���C������
void ScreenHitCheck(float *x,float *y,int gr_x,int gr_y) {

	//x��
	if (*x + gr_x > WIDTH)  *x  = WIDTH  - gr_x;

	if (*x < 0) *x = 0;
	//y��
	if (*y + gr_y > HEIGHT) *y  = HEIGHT - gr_y;

	if (*y < 0) *y = 0;
}
