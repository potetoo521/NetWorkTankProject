#pragma once
#include "DxLib.h"

#include <memory>
#include <string.h>
#include <string>
#include <sstream>
#include <list>

#define MAX 2 //�ڑ���
#define WIDTH 800 //window�T�C�Y ��
#define HEIGHT 600 //window�T�C�Y �c

//IPDATA IP_set();//IP����
using namespace std;

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
struct Pos {
	float x, y;
};

//mouse�̈ʒu���
struct MousePos {
	int x, y;
};


//�x�[�X�N���X
class Base {
private:
public:
	int ID{ -1 };//�I�u�W�F�N�g��ID
	virtual int Action(list<unique_ptr<Base*>>& base) = 0;//����
	virtual void Data_Init()=0;//�������p
	//virtual void Draw() = 0;//�`��
	//virtual bool CheckHit(float m_x, float m_y, float e_x, float e_y) = 0;

};

//�v���C���[�N���X
class PlayerData :public Base{
private:
	int img{0};
public:
	char name[8]{ "null" };//���O
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	MousePos moupos{ 0, 0 };  //mouse�̈ʒu
	int ID{ -1 };//�I�u�W�F�N�g���ʗp
	IPDATA ip{ 0,0,0,0 };//IP�A�h���X�ۑ��p

	bool mouset_f = false;//mouse���W�擾����

	//�R���X�g���N�^
	PlayerData();
	PlayerData(float _x, float _y, char* _name);

	int Action(list<unique_ptr<Base*>>& data);

	//�������p���\�b�h
	void Data_Init();

	//����
	//int Player::Action(list<Base*>* base) {
	//void Draw();
	
};


class BulletData :public Base{
private:
public:

	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	//�R���X�g���N�^
	BulletData();
	BulletData(float _x, float _y);

	
	int Action(list<unique_ptr<Base*>>& base);
	//���������\�b�h
	void Data_Init();


};

//����M�f�[�^�p�̃N���X
class SendData {
private:
public:
	PlayerData data[MAX];
	BulletData b_data[MAX];
};












