#pragma once
#include "DxLib.h"
#include <list>
#include <memory>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

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
	float x,y;
};

//�x�[�X�N���X
class Base {
private:
public:
	int ID{ -1 };//�I�u�W�F�N�g��ID
	virtual int Action(list<unique_ptr<Base>>& base) = 0;//����
	virtual void Draw() = 0;//�`��
	//virtual bool CheckHit(float m_x, float m_y, float e_x, float e_y) = 0;

};

//�v���C���[
class Player :public Base
{
private:
	int img{ 0 };//�摜

public:
	char name[8]{ "null" }; //���O
	Pos pos{ 0.0f,0.0f };   //�ʒu
	Vec vec{ 0.0f,0.0f };   //�ړ��x�N�g��
	MousePos moupos{0, 0};  //mouse�̈ʒu
	int ID{ -1 };           //�I�u�W�F�N�g���ʗp
	IPDATA ip{ 0,0,0,0 };   //IP�A�h���X�ۑ��p

	bool mouset_f = false;  //mouse���W�擾����

	//�R���X�g���N�^
	Player();
	Player(float _x, float _y, char* _name);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y);

};

//�e��
class Bullet :public Base
{
private:
	int img{ 0 };//�摜

public:
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	//�R���X�g���N�^
	Bullet(float _x,float _y,float _vx,float _vy);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	//bool CheckHit(float m_x, float m_y, float e_x, float e_y);

	


};

//
////�e��
//class BulletData {
//private:
//public:
//
//	Pos pos{ 0.0f,0.0f };//�ʒu
//	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
//	//�R���X�g���N�^
//	BulletData();
//	BulletData(float _x, float _y);
//	//���������\�b�h
//	void Data_Init();
//
//
//};




