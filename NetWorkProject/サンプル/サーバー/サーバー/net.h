#pragma once
#include "chara.h"

enum {
	T1,//�X���b�h�P
	T2,//�X���b�h2
	T3,//�X���b�h3
	T4,//�X���b�h4
	TAMA//�e
};

//�v���C���[�̃f�[�^
typedef struct Player_Data {
	Player p_data[MAX];
	Vec tama_vec[MAX]{ {0.0f,0.0f}, {0.0f,0.0f}, {0.0f,0.0f}, {0.0f,0.0f} };//�e�̈ړ��x�N�g��
	IPDATA IP[MAX] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	int NetHandle[MAX] = { -1, -1, -1, -1 };//�l�b�g�n���h��
	int flg[MAX] = { -1,-1,-1,-1 };//���݂̗L��(1�ȏ㑶��)
}Player_Data;


//���M�p�f�[�^
class SEND_SERVER_DATA{
private:
public:
	int flg[MAX] = { -1,-1,-1,-1 };//���݂̗L��(1�ȏ㑶��)
	Point pos[MAX];//�v���C���[�̈ʒu
	Vec B_vec[MAX];//�e�̈ړ��x�N�g��
};

//�N���C�A���g�p
class  SEND_CLIENT_DATA{
private:
public:
	Point pos[MAX];//�v���C���[�̈ʒu
	Vec m_vec{ 0.0f,0.0f };//�e�̈ړ��x�N�g��
};