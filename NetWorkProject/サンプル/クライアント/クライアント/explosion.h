#pragma once
#include "main.h"
//����

class Explosion : public Bace {
private:
public:
	int img{ -1 };
	int flag{ -1 };

	Point pos{ 0.0f,0.0f };
	int RectX, RectY;//�؂���ʒu
	int anim_cnt{ 0 };//�A�j���[�V�����J�E���g�p

	//�R���X�g���N�^
	Explosion(float _x, float _y);

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();

};