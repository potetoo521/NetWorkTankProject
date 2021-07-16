#pragma once
#include "main.h"

//�v���C���[
class Player :public Bace{
private:
public:
	char name[8] = { "null" };//���O
	Point pos{ 0.0f,0.0f };//�ʒu
	bool hit_flag = false;    //�e�ۂ̃q�b�g����t���O

	//�R���X�g���N�^
	Player(float _x, float _y);//�N���C�A���g�p
	Player();//�T�[�o�[�p
	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();

	//������
	void Init();
};

//���̃v���C���[
class AnyPlayer :public Bace {
private:
public:
	char name[8] = { "null" };//���O
	Point pos{ 0.0f,0.0f };//�ʒu
	//�R���X�g���N�^
	AnyPlayer(int _id);

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();

};
//�e
class Bullet :public Bace {
private:
public:

	Vec bullet_vec{ 0.0f,0.0f };//�e�̈ړ��x�N�g��
	Pos bullet_pos{ 0.0f,0.0f };//�e�̈ʒu
	bool hit_flag = false;    //�e�ۂ̃q�b�g����t���O

	//�R���X�g���N�^
	Bullet(float vx, float vy, float px, float py,char id);
	Bullet();

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();
};

