#pragma once
#include "main.h"

//�R���X�g���N�^
PlayerData::PlayerData(float _x, float _y, char* _name) {
	pos.x = _x;
	pos.y = _y;

	strcpy_s(name, _name);
}

//�C�j�V�����C�Y(������)
void PlayerData::Data_Init() {
	strcpy_s(name, "null");

	ip.d1 = 0; ip.d2 = 0; ip.d3 = 0; ip.d4 = 0;

	pos.x = 0.0f;
	pos.y = 0.0f;

	ID = -1;

}

PlayerData::PlayerData() {}

//Action���s
int PlayerData::Action(list<unique_ptr<Base*>>& data) {

	return 0;
}





////�`��(�T�[�o�[���ł͕`��͂��Ȃ�)
//void Player::Draw() {
//
//}
//

//CheckHit�֐��̒�`
//float m_x = �I�u�W�F�N�gA�� X ���W
//float m_y = �I�u�W�F�N�gA�� Y ���W

//float e_x = �I�u�W�F�N�gB�� X ���W
////float e_y = �I�u�W�F�N�gB�� Y ���W
//bool Player::CheckHit(float m_x, float m_y, float e_x, float e_y)
//{
//
//	float len = sqrt((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));
//
//
//
//	if (len <= 32)//32 == ���S�܂ł̋���
//	{
//
//		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
//	}
//	else
//	{
//		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
//	}
//}
