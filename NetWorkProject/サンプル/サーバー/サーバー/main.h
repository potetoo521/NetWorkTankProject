#pragma once
#include "DxLib.h"

#include <stdarg.h>
#include <string>
#include <sstream>

#include <list>
#include <memory>

using namespace std;

#define MAX 4//�ڑ���

#define WIDTH 800
#define HEIGHT 600

IPDATA IP_set();//IP����

enum state {
	CONNECTING,//�ڑ���
	ONLINE,//�I�����C��
	GAME//�Q�[����
};

typedef struct Vec {
	float x, y;
}Vec;

typedef struct Point {
	float x, y;
}Pos;


//---�֐��錾---
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel);//CheckHit�֐��̐錾

bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y); //ScreenHitCheck�֐��̐錾

Vec Vector_Plus(Vec a_vec, Vec b_vec);  //�x�N�g�����m�𑫂��֐�

Vec Vector_Minus(Vec a_vec, Vec b_vec); //�x�N�g�����m�������֐�

Vec Normalize_Vec(Vec vec);             //�x�N�g���𐳋K������֐�

Vec Direction_Vec(Pos a_pos, Pos b_pos);//�����x�N�g���擾�֐�

float Vector_Length(Vec vec);           //�x�N�g���̒������擾����֐�

Pos PosVec_Minus(Pos a_pos, Vec b_vec); //���W�ƃx�N�g���𑫂��֐�

Pos PosVec_Plus(Pos a_vec, Vec b_vec);  //���W�ƃx�N�g���������֐�

bool IsVariable(Pos a_pos);//Pos�l�������Ă��邩�𔻒�֐�

bool IsVariable(Vec a_pos);//Vec�l�������Ă��邩�𔻒�֐�

//�x�[�X�N���X�i�e�Ŏg�p�j
class Bace {
private:
public:
	int img{ -1 };//�摜�f�[�^
	char ID{ -1 };

	Point pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��

	virtual int Action(list<unique_ptr<Bace>>& bace) = 0;
	virtual void Draw() = 0;
};
