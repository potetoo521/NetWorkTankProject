#pragma once
#include "character.h"
#include "DxFunctionWin.h"



//�R���X�g���N�^
Player::Player(float _x, float _y, char* _name) {
	strcpy_s(name, "null");
	ID = 0;
	img = LoadGraph("image/maid.png");
	mouset_f = false;//mouse���W�擾����
	ip.d1 = 0; ip.d2 = 0; ip.d3 = 0; ip.d4 = 0;//IP�A�h���X

	strcpy_s(name, _name);
}

Player::Player(){}

//����
int Player::Action(list<unique_ptr<Base>>& base)
{
	//�L�[����
	vec.x = 0.0f,vec.y = 0.0f;
	if (CheckHitKey(KEY_INPUT_UP))    vec.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_DOWN))  vec.y =  4.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))  vec.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x =  4.0f;

		//�e�۔��˖ڕW�擾����
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		//�����ꂽ��
		if (mouset_f == false) {//mouse�z�[���h��Ԋm�F

			mouset_f = true;//�}�E�X���

			int x = (int)moupos.x;//int�^�ɃL���X�g
			int y = (int)moupos.y;

			//mouse�J�[�\���̈ʒu���擾(int�^)
			GetMousePoint(&x, &y);

			moupos.x = (float)x; //mouse�ʒu���i�[
			moupos.y = (float)y;

			moupos.x = moupos.x - pos.x;//�����x�N�g���擾
			moupos.y = moupos.y - pos.y;

			float mag = sqrt(moupos.x * moupos.x + moupos.y * moupos.y);//����

			moupos.x = -moupos.x / mag;//���K�������x�N�g��
			moupos.y = -moupos.y / mag;

			//�e�ۍ쐬
			Bullet* bullet = new Bullet(pos.x,pos.y,moupos.x, moupos.y);//�ʒu�ƕ����x�N�g��
			auto add = (unique_ptr<Base>) bullet;
			base.emplace_back(move(add));//���X�g��bullet��ǉ�

		}
	}
	else {//������Ă��Ȃ���
		mouset_f = false;
	}


	DrawFormatString(0, 64, GetColor(255, 255, 255),
		"mouse_x:%f          mouse_y:%f"    "pos_x:%d          pos_y:%d",
		moupos.x,
		moupos.y,
		pos.x,
		pos.y
	);

	return 0;
	
}

//�`��
void Player::Draw(){

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
