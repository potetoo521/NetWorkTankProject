#pragma once
#include "DxLib.h"
#include "character.h"
#include <string.h>
#include <string>
#include <sstream>

#define MAX 4 //�ڑ���
#define WIDTH 800 //window�T�C�Y ��
#define HEIGHT 600 //window�T�C�Y �c

#define DESTROY_ID -999 //�폜ID

using namespace std;

IPDATA IP_set();//IP����

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

//����M�f�[�^�p�̃N���X
class SendData {
private:
public:

	Player data[MAX];
};






