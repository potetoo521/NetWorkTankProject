#pragma once
#include "DxLib.h"

#include <stdarg.h>
#include <string>
#include <sstream>

#include <list>
#include <memory>

using namespace std;

#define MAX 4//�ڑ���

#define WIDTH 800
#define HEIGHT 600

#define IMGWIDTH64 64
#define IMGHEIGHT64 64

IPDATA IP_set();//IP����

enum OBJ {
	PLAYER,
	ANYPLAYER,
	BULLET,
	MOUSE
};

enum state {
	CONNECTING,//�ڑ���
	ONLINE,//�I�����C��
	GAME//�Q�[����
};

typedef struct Vec {
	float x, y;
}Vec;

typedef struct Point {
	float x, y;
}Point;

//�x�[�X�N���X�i�e�Ŏg�p�j
class Bace {
private:
public:
	int img{ -1 };//�摜�f�[�^
	char ID{ -1 };
	bool FLAG{ false };

	Point pos{ 0.0f,0.0f };//�ʒu
	Vec vec{ 0.0f,0.0f };//�ړ��x�N�g��

	virtual int Action(list<unique_ptr<Bace>>& bace) = 0;
	virtual void Draw() = 0;
};
