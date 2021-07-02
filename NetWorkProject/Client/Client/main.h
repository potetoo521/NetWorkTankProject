#pragma once
#include "DxLib.h"
#include <string.h>
#include <string>
#include <sstream>

#define MAX 2 //�ڑ���
#define MAXBULLET 10 //�e�ې�
#define WIDTH 800.0f //window�T�C�Y ��
#define HEIGHT 600.0f //window�T�C�Y �c

#define DESTROY_ID -999 //�폜ID

using namespace std;

const int Destroy_ID = -999;//�j��R�[�h
const float B_Speed = 5.0f; //�e�ۃX�s�[�h
const int   B_Bound = 2;    //�e��bound��
const float P_Speed = 4.0f; //�v���C���[�X�s�[�h

IPDATA IP_set();//IP����


//�ړ��x�N�g��
struct Vec {
	float x, y;
};

//�ʒu���
struct Pos {
	float x, y;
};

//mouse�ʒu���擾
struct MousePos {
	float x, y;
};

//�摜�T�C�Y
struct GraphSize { 
	int x,y; 
};  

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


//�X���b�h�̃i���o�[
enum {
	T_A,
	T_B,
	T_C,
	T_D
};


/*
//�v���C���[�N���X
class Data {
private:
public:
	char name[8]{ "null" };//���O
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	int ID{ -1 };//�I�u�W�F�N�g���ʗp
	IPDATA ip{ 0,0,0,0 };//IP�A�h���X�ۑ��p
	//�R���X�g���N�^
	Data();
	Data(float _x, float _y, char* _name);
	//�������p���\�b�h
	void Data_Init();
};*/







