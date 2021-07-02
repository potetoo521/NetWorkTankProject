#pragma once
#include "DxLib.h"
#include <list>
#include <memory>//����������ɕK�v

using namespace std;

#define WIDTH 1280.0f
#define HEIGHT 980.0f
#define FPS 60

const int Destroy_ID = -999;//�j��R�[�h
const float B_Speed = 5.0f; //�e�ۃX�s�[�h
const int   B_Bound = 2;    //�e��bound��
const float P_Speed = 4.0f; //�v���C���[�X�s�[�h

struct GraphSize { int x; int y; };   //�摜�T�C�Y

struct Pos { float x; float y; };     //�ʒu

struct Vec { float x; float y; };     //�ړ��x�N�g��

//---�֐��錾---
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel);//CheckHit�֐��̐錾

bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y);//ScreenHitCheck�֐��̐錾

Vec Vector_Plus(Vec a_vec, Vec b_vec);  //�x�N�g�����m�𑫂��֐�

Vec Vector_Minus(Vec a_vec, Vec b_vec); //�x�N�g�����m�������֐�

Vec Normalize_Vec(Vec vec);             //�x�N�g���𐳋K������֐�

Vec Direction_Vec(Pos a_pos, Pos b_pos);//�����x�N�g���擾�֐�

float Vector_Length(Vec vec);           //�x�N�g���̒������擾����֐�

Pos PosVec_Minus(Pos a_pos, Vec b_vec); //���W�ƃx�N�g���𑫂��֐�

Pos PosVec_Plus(Pos a_vec, Vec b_vec);  //���W�ƃx�N�g���������֐�