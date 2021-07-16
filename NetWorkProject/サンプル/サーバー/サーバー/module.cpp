#include "main.h"


//---�֐��錾---
//bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel);//CheckHit�֐��̐錾
//
//bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y); //ScreenHitCheck�֐��̐錾
//
//Vec Vector_Plus(Vec a_vec, Vec b_vec);  //�x�N�g�����m�𑫂��֐�
//
//Vec Vector_Minus(Vec a_vec, Vec b_vec); //�x�N�g�����m�������֐�
//
//Vec Normalize_Vec(Vec vec);             //�x�N�g���𐳋K������֐�
//
//Vec Direction_Vec(Pos a_pos, Pos b_pos);//�����x�N�g���擾�֐�
//
//float Vector_Length(Vec vec);           //�x�N�g���̒������擾����֐�
//
//Pos PosVec_Minus(Pos a_pos, Vec b_vec); //���W�ƃx�N�g���𑫂��֐�
//
//Pos PosVec_Plus(Pos a_vec, Vec b_vec);  //���W�ƃx�N�g���������֐�
//
//bool IsVariable(Pos a_pos);//Pos�l�������Ă��邩�𔻒�֐�
//
//bool IsVariable(Vec a_pos);//Vec�l�������Ă��邩�𔻒�֐�


bool IsVariable(Pos a_pos) {

	//�ϐ��̒��g�������Ă���ΐ^
	if (a_pos.x != NULL && a_pos.y != NULL)
	{
		return true;
	}
	else {
		return false;
	}
}

bool IsVariable(Vec a_vec) {

	//�ϐ��̒��g��0.0f�łȂ��܂��́A���g�������Ă���ΐ^
	if (a_vec.x != NULL && a_vec.y != NULL)
	{
		return true;
	}
	else {
		return false;
	}
}

//�����x�N�g���擾�p
Vec Direction_Vec(Pos a_pos,Pos b_pos)
{
	Vec vec{ 0,0 };

	vec.x = a_pos.x - b_pos.x;//�ʒu-�ʒu
	vec.y = a_pos.y - b_pos.y;

	return vec;
}

//Vector�̒������擾
float Vector_Length(Vec vec) {

	float mag = sqrtf(vec.x * vec.x + vec.y * vec.y);//�������擾

	return mag;
}

//Vector�𐳋K��
Vec Normalize_Vec(Vec a_vec)
{
	float len = Vector_Length(a_vec);//�������擾

	a_vec.x = a_vec.x / len;//�x�N�g��vec�ƃx�N�g���̒���len�Ŋ���
	a_vec.y = a_vec.y / len;

	return a_vec;
}

//���W�ƃx�N�g���𑫂�
Pos PosVec_Plus(Pos a_pos, Vec b_vec)
{
	a_pos.x = a_pos.x + b_vec.x;//�ʒu + �x�N�g��
	a_pos.y = a_pos.y + b_vec.y;

	return a_pos;
}

//���W�ƃx�N�g��������
Pos PosVec_Minus(Pos a_pos, Vec b_vec)
{
	a_pos.x = a_pos.x - b_vec.x;//�ʒu - �x�N�g��
	a_pos.y = a_pos.y - b_vec.y;

	return a_pos;
}

//�x�N�g���𑫂�
Vec Vector_Plus(Vec a_vec, Vec b_vec)
{
	a_vec.x = a_vec.x + b_vec.x;//�x�N�g�� + �x�N�g��
	a_vec.y = a_vec.y + b_vec.y;

	return a_vec;
}

//�x�N�g��������
Vec Vector_Minus(Vec a_vec, Vec b_vec)
{
	a_vec.x = a_vec.x - b_vec.x;//�x�N�g�� - �x�N�g��
	a_vec.y = a_vec.y - b_vec.y;

	return a_vec;
}

//�����蔻��  �摜�c����(pixel)����v���Ă���ꍇ�̂�
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel) {

	float magLen = (p_pixel + e_pixel) / 2;

	float len = sqrtf((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));//���ς̒������擾

	if (len <= magLen)//MagLen == len�܂ł̋���
	{
		return true;//���茋�ʓ������Ă���( �^ )��Ԃ�
	}
	else
	{
		return false;//���茋�ʓ������Ă��Ȃ�( �U )��Ԃ�
	}
};

//��ʂ̒[�ɗ������ʊO�ɏo�Ȃ��p�Ɉʒu���C������
bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y) {

	//x��
	if (*x + gr_x > WIDTH) {
		*x = WIDTH - gr_x;
		return true;
	}
	if (*x < 0) {
		*x = 0;
		return true;
	}
	//y��
	if (*y + gr_y > HEIGHT) {
		*y = HEIGHT - gr_y;
		return true;
	}
	if (*y < 0) {
		*y = 0;
		return true;
	}
	return false;
}