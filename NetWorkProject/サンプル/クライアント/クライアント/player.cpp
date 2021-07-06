#pragma once
#include "chara.h"
//�v���C���[

//�N���C�A���g�p�R���X�g���N�^
Player::Player(float _x, float _y) {
	img = LoadGraph("image\\koiking.png");

	pos.x = _x;
	pos.y = _y;

	FLAG = true;
}
//�T�[�o�[�p�R���X�g���N�^
Player::Player() {

}
//����
//0:�ړ�����@0�ȊO�F�ړ��ł��Ȃ�
int Player::Action(list<unique_ptr<Bace>>& bace) {
	vec.x = 0.0f; vec.y = 0.0f;

	//�L�[����
	if (CheckHitKey(KEY_INPUT_W)) vec.y = -4.0f;//��
	if (CheckHitKey(KEY_INPUT_S)) vec.y = 4.0f;//��
	if (CheckHitKey(KEY_INPUT_A)) vec.x = -4.0f;//�E
	if (CheckHitKey(KEY_INPUT_D)) vec.x = 4.0f;//��

	//�̈攻��
	if (pos.x + vec.x < 0.0f || pos.x + vec.x > 736.0f) vec.x = 0.0f;
	if (pos.y + vec.y < 0.0f || pos.y + vec.y > 536.0f) vec.y = 0.0f;

	//���W�X�V
	pos.x += vec.x;
	pos.y += vec.y;

	//�e�Ƃ̓����蔻��
	for (auto i = bace.begin(); i != bace.end(); i++) {
		(*i)->Action(bace);
	}

	//�ړ��x�N�g���̏�Ԃɂ���Ė߂�l��ς���
	if (vec.x != 0.0f || vec.y != 0.0f) {
		return 1;
	}

	return 0;
}

//�`��
void Player::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}

//������
void Player::Init() {
	img = -1;
	strcpy_s(name, "null");
	pos.x = 0.0f;
	pos.y = 0.0f;
}