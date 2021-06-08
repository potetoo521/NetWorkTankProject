#pragma once
#include "main.h"



struct MousePos {
	int mouse_x, mouse_y;


};


//�v���C���[
class Player :public Base
{
private:
	int img{ 0 };//�摜

public:
	char name[8]{ "null" };//���O
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	MousePos mop{0, 0};  //mouse�̈ʒu
	int ID{ -1 };//�I�u�W�F�N�g���ʗp
	IPDATA ip{ 0,0,0,0 };//IP�A�h���X�ۑ��p

	bool mouset = false;//mouse���W�擾����

	//�R���X�g���N�^
	Player();
	Player(float _x, float _y, char* _name);




	int Action(list<Base*>* base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y);

};

//�G
class Bullet :public Base
{
private:
	int img{ 0 };//�摜

public:
	Pos pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��
	//�R���X�g���N�^
	Bullet(float _x,float _y);

	int Action(list<Base*>* base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y) { return 0;};

	


};