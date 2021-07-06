#pragma once
#include "explosion.h"

//�R���X�g���N�^
Explosion::Explosion(float _x, float _y) {
	//�摜�f�[�^
	img = LoadGraph("image\\ex.png");

	//�`��ʒu
	pos.x = _x;
	pos.y = _y;

	//�؂���ʒu
	RectX = 0;
	RectY = 0;

}

//����
int Explosion::Action(list<unique_ptr<Bace>>& bace) {
	anim_cnt++;

	if (anim_cnt % 8 == 0) {
		RectX += 64;
	}

	if (RectX == 256) {
		RectX = 0;
		RectY += 64;
	}
	if (RectY == 128) FLAG = false;

	return 0;
}

//�`��
void Explosion::Draw() {
	DrawRectGraphF(pos.x, pos.y, RectX, RectY, IMGWIDTH64, IMGHEIGHT64, img, true, false);
}
