#pragma once
#include "main.h"

//�}�E�X�N���X
class Mouse {
private:
public:
	int img{ -1 };//�摜
	float rad{ 0.0f };//�`�悷�鎞�̊p�x
	Point pos{ 0.0f,0.0f };
	Vec v{ 0.0f,0.0f };//�ړ��x�N�g��
	Vec b_v{ 0.0f,0.0f };//�e�̈ړ��x�N�g��

	int button_push{ 0 };//�{�^������

	//�R���X�g���N�^
	Mouse();

	int Action(list<unique_ptr<Bace>>& bace, float px, float py);//�{�^���̏�Ԃ�Ԃ��B(�v���C���[��x���W,�v���C���[��y���W)

	void Drwa();
};
