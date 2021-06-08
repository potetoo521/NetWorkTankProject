#pragma once
#include "character.h"

//�R���X�g���N�^
Player::Player(float _x, float _y, char* _name) {
	ID = 0;
	img = LoadGraph("image/maid.png");
	mouset = false;//mouse���W�擾����

	strcpy_s(name, _name);
}

//����
int Player::Action(list<Base*>* base) {
	//�L�[����
	Vec v{ 0.0f,0.0f };
	if (CheckHitKey(KEY_INPUT_UP)) v.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) v.y = 4.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) v.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) v.x = 4.0f;
	

		//�e�۔��˖ڕW�擾����
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//�����ꂽ��
		mouset = true;

		//mouse�J�[�\���̈ʒu���擾
		mouset = GetMousePoint(&mop.mouse_x, &mop.mouse_y);

	}
	else {
		mouset = false;
	}
	return 0;
}

//�`��
void Player::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}





//CheckHit�֐��̒�`
//float m_x = �I�u�W�F�N�gA�� X ���W
//float m_y = �I�u�W�F�N�gA�� Y ���W

//float e_x = �I�u�W�F�N�gB�� X ���W
//float e_y = �I�u�W�F�N�gB�� Y ���W
bool Player::CheckHit(float m_x, float m_y, float e_x, float e_y)
{

	float len = sqrt((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));



	if (len <= 32)//32 == ���S�܂ł̋���
	{

		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
	}
	else
	{
		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
	}

}
