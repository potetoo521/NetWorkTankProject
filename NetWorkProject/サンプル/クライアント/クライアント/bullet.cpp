#pragma once
#include "chara.h"
//�e

//�R���X�g���N�^
Bullet::Bullet(float vx, float vy,float px,float py,char id) {
	img = LoadGraph("image\\bullet.png");

	pos.x = px+16;
	pos.y = py+16;
	ID = id;
	vec.x = vx;
	vec.y = vy;

	FLAG = true;
}

//����
int Bullet::Action(list<unique_ptr<Bace>>& bace) {
	pos.x += vec.x;
	pos.y += vec.y;

	//��ʊO�ɏo����폜
	if (pos.x<0 || pos.y<0 || pos.x>WIDTH - 32 || pos.y>HEIGHT - 32) {
		FLAG = false;
	}
	if (ID == DESTROY_ID) {
		FLAG = false;
	}

	for (auto a = bace.begin(); a != bace.end(); a++) {//���X�g
		Pos p_pos = (*a).get()->pos;
		if (CheckHit(p_pos.x,p_pos.y,pos.x,pos.y,64.0f,64.0f)) {//�v���C���[�̈ʒu�ƒe�ۂ̈ʒu,�傫��
			(*a).get()->FLAG = true;//�������Ă���
		}
	}


	return 0;
}

//�`��
void Bullet::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}

//�T�[�o�[�p�R���X�g���N�^
Bullet::Bullet() {

}