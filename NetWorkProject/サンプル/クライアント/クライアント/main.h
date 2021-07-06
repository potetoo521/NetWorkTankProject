#pragma once
#include "DxLib.h"

#include <stdarg.h>
#include <string>
#include <sstream>

#include <list>
#include <memory>

using namespace std;

#define MAX 4//接続数

#define WIDTH 800
#define HEIGHT 600

#define IMGWIDTH64 64
#define IMGHEIGHT64 64

IPDATA IP_set();//IP入力

enum OBJ {
	PLAYER,
	ANYPLAYER,
	BULLET,
	MOUSE
};

enum state {
	CONNECTING,//接続中
	ONLINE,//オンライン
	GAME//ゲーム中
};

typedef struct Vec {
	float x, y;
}Vec;

typedef struct Point {
	float x, y;
}Point;

//ベースクラス（弾で使用）
class Bace {
private:
public:
	int img{ -1 };//画像データ
	char ID{ -1 };
	bool FLAG{ false };

	Point pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル

	virtual int Action(list<unique_ptr<Bace>>& bace) = 0;
	virtual void Draw() = 0;
};
