#pragma once
#include "chara.h"
//�v���C���[

//�N���C�A���g�p�R���X�g���N�^
Player::Player(float _x,float _y) {
	img = LoadGraph("image\\koiking.png");
	
	pos.x = _x;
	pos.y = _y;
}

//�T�[�o�[�p�R���X�g���N�^
Player::Player() {

}

//����
int Player::Action(list<unique_ptr<Bace>>& bace) {
	vec.x = 0.0f; vec.y = 0.0f;

	if (CheckHitKey(KEY_INPUT_W)) vec.y = -4.0f;//��
	if (CheckHitKey(KEY_INPUT_S)) vec.y = 4.0f;//��
	if (CheckHitKey(KEY_INPUT_A)) vec.x = -4.0f;//�E
	if (CheckHitKey(KEY_INPUT_D)) vec.x = 4.0f;//��

	pos.x += vec.x;
	pos.y += vec.y;

	if (pos.x < 0.0f) pos.x = 0.0f;
	if (pos.x > 736.0f) pos.x = 736.0f;
	if (pos.y < 0.0f) pos.y = 0.0f;
	if (pos.y > 536.0f) pos.y = 536.0f;

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