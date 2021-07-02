#pragma once
#include "DxLib.h"
#include <list>
#include <memory>

#include "main.h"

using namespace std;

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
	char name[8]{ "null" };  //���O
	Pos pos{ 0.0f,0.0f };    //�ʒu
	Vec vec{ 0.0f,0.0f };    //�ړ��x�N�g��
	Pos moupos{0, 0};        //mouse�̈ʒu
	Vec mouvec{ 0,0 };       //mouse�x�N�g��
	GraphSize gr_size{ 0,0 };//�摜�T�C�Y
	int ID{ -1 };            //�I�u�W�F�N�g���ʗp
	IPDATA ip{ 0,0,0,0 };    //IP�A�h���X�ۑ��p

	bool mouset_f = false;   //mouse���W�擾����

	//�R���X�g���N�^
	Player();
	Player(float _x, float _y, char* _name);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y);

};

//����M�f�[�^�p�̃N���X
class SendData{
private:
public:

	Player player[MAX];
	//Bullet bullet[MAXBULLET];
};


//�e��
class Bullet :public Base
{
private:
	int img{ 0 };//�摜

public:
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	GraphSize gr_size{ 0,0 };//�摜�T�C�Y
	int owner_Id = -1;//�쐬���̃I�u�W�F�N�gID�i�[�p
	int boundNum = 0; //�e�ۂ̒��˕Ԃ��
	//�R���X�g���N�^
	Bullet(float _x, float _y, float _vx, float _vy, int id);

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




