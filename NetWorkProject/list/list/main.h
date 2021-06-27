#pragma once
#include "DxLib.h"
#include <list>
#include <memory>//����������ɕK�v

using namespace std;

#define WIDTH 1280.0f
#define HEIGHT 980.0f
#define FPS 60

const int Destroy_ID = -999;   //�j��ID
const int B_Bound = 2;         //�e�ۂ̃o�E���h��
const float B_Speed = 1.0f;    //�e�ۂ̃X�s�[�h
const float P_Speed = 4.0f;    //Player�̈ړ��X�s�[�h

struct MousePos { float x; float y; };//mouse�x�N�g�����擾

struct GraphSize { int x; int y; };//�摜�T�C�Y

struct Pos { float x; float y; };//�ʒu

struct Vec { float x; float y; };//�ړ��x�N�g��

//CheckHitDraw�֐��̐錾
void CheckHitDraw(Pos pos,GraphSize p_pixel);

//CheckHit�֐��̐錾
bool CheckHit(Pos a_pos, Pos b_pos, GraphSize a_pixel, GraphSize b_pixel);

//ScreenHitCheck�֐��̐錾
void ScreenHitCheck(Pos* pos, GraphSize gr);
