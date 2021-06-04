#pragma once
#include "DxLib.h"

#include <string.h>
#include <string>
#include <sstream>

#define MAX 2 //�ڑ���
#define WIDTH 800 //window�T�C�Y ��
#define HEIGHT 600 //window�T�C�Y �c

//IPDATA IP_set();//IP����

//�X���b�h�̃i���o�[
enum {
	T_A,
	T_B,
	T_C,
	T_D
};

//�ړ��x�N�g��
struct Vec {
	float x, y;
};

//�ʒu���
struct Point {
	float x, y;
};

//mouse�̈ʒu���
struct MousePos {
	int x, y;
};


//�v���C���[�N���X
class Data {
private:
public:
	char name[8]{ "null" };//���O
	Point pos{ 0.0f,0.0f };//�ʒu
	MousePos mouPos{ 0,0 };//mouse�̈ʒu

	int ID{ -1 };//�I�u�W�F�N�g���ʗp
	IPDATA ip{ 0,0,0,0 };//IP�A�h���X�ۑ��p
	//�R���X�g���N�^
	Data();
	Data(float _x, float _y, char* _name);
	//�������p���\�b�h
	void Data_Init();
};

class BulletData {
private:
public:

	Point pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	//�R���X�g���N�^
	BulletData();
	BulletData(float _x, float _y);
	//���������\�b�h
	void Data_Init();


};



//����M�f�[�^�p�̃N���X
class SendData {
private:
public:
	Data data[MAX];
	BulletData b_data[MAX];
};












