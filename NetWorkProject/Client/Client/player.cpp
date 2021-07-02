#pragma once
#include "character.h"
#include "DxFunctionWin.h"

//�R���X�g���N�^
Player::Player(float _x, float _y, char* _name) {
	strcpy_s(name, "null");
	img = LoadGraph("image/maid.png");//�摜��ǂݍ���

	GetGraphSize(img, &gr_size.x, &gr_size.y);//�摜�T�C�Y���擾

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
	if (CheckHitKey(KEY_INPUT_UP))    vec.y = -P_Speed;
	if (CheckHitKey(KEY_INPUT_DOWN))  vec.y =  P_Speed;
	if (CheckHitKey(KEY_INPUT_LEFT))  vec.x = -P_Speed;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x =  P_Speed;

		//�e�۔��˖ڕW�擾����
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		//�����ꂽ��
		if (mouset_f == false) {//mouse�z�[���h��Ԋm�F

			mouset_f = true;//�}�E�X���

			int x = (int)moupos.x;//GetMousePoint�ɓ���邽��int�^�ɃL���X�g
			int y = (int)moupos.y;

			GetMousePoint(&x, &y);//mouse�J�[�\���̈ʒu���擾

			moupos.x = (float)x;  //mouse�ʒu���i�[
			moupos.y = (float)y;

			mouvec = Normalize_Vec(Direction_Vec(moupos, pos));//�����x�N�g���𐳋K��



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

	//�L�����摜
	DrawGraphF(pos.x, pos.y, img, TRUE);
	
	//���O
	DrawStringF(pos.x,pos.y,
		name,
		GetColor(255, 255, 255)
	);


}
