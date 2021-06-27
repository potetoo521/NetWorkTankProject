#pragma once
#include "main.h"


//�x�[�X�N���X
class Base {
private:
public:
	int ID{ -1 };//�I�u�W�F�N�g��ID
	virtual int Action(list<unique_ptr<Base>>& base) = 0;
	//virtual int Action(list<Base*>* base) = 0;//����
	virtual void Draw() = 0;//�`��

};

//�v���C���[
class Player :public Base
{
private:
	int img{ 0 };//�摜
	int sound{ -1 };//�T�E���h
public:
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	MousePos moupos{ 0, 0 };  //mouse�̈ʒu
	GraphSize gr_size{ 0,0 };//�摜�T�C�Y
	bool mouset_f =false;
	//�R���X�g���N�^
	Player();
	
	int Action(list<unique_ptr<Base>>& base);
	//int Action(list<Base*>* base);
	void Draw();
	

};

//�G
class Enemy :public Base
{
private:
	int img{ 0 };//�摜

public:
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	

	//�R���X�g���N�^
	Enemy(float _x,float _y);

	int Action(list<Base*>* base);
	void Draw();
	
	


};

//�e��
class Bullet :public Base
{
private:
	int img{ 0 };//�摜

public:
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	GraphSize gr_size{ 0,0};//�摜�T�C�Y
	int owner_Id = -1;//�쐬���̃I�u�W�F�N�gID�i�[�p
	int boundNum = 0; //�e�ۂ̒��˕Ԃ��
	//�R���X�g���N�^
	Bullet(float _x, float _y, float _vx, float _vy,int id);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();

	Pos posd{ 0.0f,0.0f };//�ʒu//�f�o�b�O
};