#pragma once
#include "mouse.h"
#include "chara.h"

//�R���X�g���N�^
Mouse::Mouse() {
	img = LoadGraph("image\\mouseArrow.png");
}

//����
//�{�^���̏�Ԃ�Ԃ��B(�v���C���[��x���W,�v���C���[��y���W)
int Mouse::Action(list<unique_ptr<Bace>>& bace, float px, float py) {
	int mx, my;
	GetMousePoint(&mx, &my);//�}�E�X�̈ʒu���擾

	//���
	//�v���C���[�ƃ}�E�X�̊Ԃ̃x�N�g�������߂�
	v.x = mx - (int)px;
	v.y = my - (int)py;
	float d = sqrtf((px - mx) * (px - mx) + (py - my) * (py - my));//���������߂�
	//�`��ʒu�̌v�Z
	//���K�����āA�v���C���[����60pix�̈ʒu�ɐݒ�
	pos.x = (v.x / d) * 60 + px;
	pos.y = (v.y / d) * 60 + py;
	//����`�悷��ꍇ�̊p�x���v�Z
	rad = atan2((double)pos.x - mx, (double)pos.y - my);

	//�}�E�X�̃{�^���N���b�N������
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && button_push==0) {
		//��΂������x�N�g�����v�Z
		Vec v;
		v.x = pos.x - px;
		v.y = pos.y - py;
		float d = sqrtf(v.x * v.x + v.y * v.y);
		v.x = (v.x / d) * 4.0f;
		v.y = (v.y / d) * 4.0f;
		//�e�𐶐�
		bace.emplace_back((unique_ptr<Bace>)new Bullet(v.x, v.y, px, py));
		//�e�̈ړ��x�N�g��
		b_v.x = v.x;
		b_v.y = v.y;

		//�{�^���̏����X�V
		button_push = 1;
	}else if((GetMouseInput() & MOUSE_INPUT_LEFT)==0)	//�}�E�X���{�^���𗣂�����
	{
		//�{�^���̏����X�V
		button_push = 0;
	}

	return button_push;
}

void Mouse::Drwa() {
	DrawRotaGraph((int)pos.x + 32, (int)pos.y + 32, 1.0, -rad, img, TRUE);
}
