#pragma once
#include "chara.h"
//���̃v���C���[

//�R���X�g���N�^
AnyPlayer::AnyPlayer(int _id) {
	img = LoadGraph("image\\hitokage.png");
	ID = _id;

	FLAG = true;
}

//����
//0:�ړ�����@0�ȊO�F�ړ��ł��Ȃ�
int AnyPlayer::Action(list<unique_ptr<Bace>>& bace) {
	return -1;
}

//�`��
void AnyPlayer::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}