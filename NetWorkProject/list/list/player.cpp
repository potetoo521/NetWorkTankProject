#pragma once
#include "character.h"

//�R���X�g���N�^
Player::Player() {
	ID = 0;
  	img = LoadGraph("image/maid.png");

	GetGraphSize(img, &gr_size.x, &gr_size.y);//�摜�T�C�Y���擾

	//gr_size.x = gr_size.x / 2;//�摜�T�C�Y��
	//gr_size.y = gr_size.y / 2;
	pos.x = 100.0f;//�e�X�g
	pos.y = 100.0f;

	SetMouseDispFlag(FALSE);//�}�E�X�\���Ȃ�

	//sound = LoadSoundMem("sound/ES_SomethingGood.wav");
}

//����
//int Player::Action(list<Base*>* base) {
int Player::Action(list<unique_ptr<Base>>& base) {
	//�L�[����
	Vec v{ 0.0f,0.0f };
	if (CheckHitKey(KEY_INPUT_UP))    v.y = -P_Speed;
	if (CheckHitKey(KEY_INPUT_DOWN))  v.y =  P_Speed;
	if (CheckHitKey(KEY_INPUT_LEFT))  v.x = -P_Speed;
	if (CheckHitKey(KEY_INPUT_RIGHT)) v.x =  P_Speed;

	//�e�۔��˖ڕW�擾����
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		//�����ꂽ��
		if (mouset_f == false) {//mouse�z�[���h��Ԋm�F

			mouset_f = true;//�}�E�X���

			int x = (int)moupos.x;
			int y = (int)moupos.y;

			GetMousePoint(&x, &y);//mouse�J�[�\���̈ʒu���擾
			
			moupos.x = (float)x;  //mouse�ʒu���i�[
			moupos.y = (float)y;

			mouvec = Normalize_Vec(Direction_Vec(moupos, pos));//�����x�N�g���𐳋K��

			//�e�ۍ쐬
			Bullet* bullet = new Bullet(pos.x, pos.y, mouvec.x, mouvec.y,ID);//�ʒu�ƕ����x�N�g��
			auto add = (unique_ptr<Bullet>) bullet;
			base.emplace_back(move(add));//���X�g��bullet��ǉ�

		}
	}
	else {//������Ă��Ȃ���
		mouset_f = false;
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {//�f�o�b�O�pbullet�폜

		for (auto i = base.begin(); i != base.end(); i++) {
			if (((Bullet*)(*i).get())->ID == 1)
			{
				i = base.erase(i);
				if (i == base.end())break;
			}
		}
	}

	//��ʊO�����蔻��
	ScreenHitCheck(&pos.x, &pos.y,gr_size.x,gr_size.y);

	//�ړ��x�N�g�������Z
	pos.x += v.x;
	pos.y += v.y;

	return 0;
}

//�`��
void Player::Draw() {
	
	int mx = 0, my = 0;//�}�E�X�ʒu
	GetMousePoint(&mx, &my);

	DrawLine(pos.x, pos.y, mx, my,GetColor(0,0,255));//����`��


	float len = sqrtf( pos.x *  pos.x +  pos.y * pos.y);//���ς̒������擾
//	DrawCircle(pos.x, pos.y, sqrtf(pos.x * pos.x + pos.y * pos.y), GetColor(255, 0, 0), TRUE);


	//�}�E�X�ʒu��\��
	DrawCircle(mx , my, sqrtf(40), GetColor(255, 0, 0), TRUE);

	//�摜�\��
	DrawGraphF(pos.x, pos.y, img, TRUE);
}




//
////�}�E�X�̈ʒu���擾
//if (flag == true)
//{
//	m_mou_bx = (float)Input::GetPosX();
//	m_mou_by = (float)Input::GetPosY();
//
//	bx = (m_mou_bx - m_bx) * m_vx;
//	by = (m_by - m_mou_by) * m_vy;
//
//	flag = false;
//}
//
//float r = 0.0f;
//r = bx * bx + by * by;
//r = sqrt(r);//r �����[�g�����߂�
//
////������0���ǂ������ׂ�
//if (r == 0.0f)
//{
//	;//0�Ȃ牽�����Ȃ�
//}
//else
//{
//	//���K�����s��
//	m_vx = 1.0f / r * bx;
//	m_vy = 1.0f / r * by;
//}