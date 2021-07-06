#pragma once
#include "main.h"

//プレイヤー
class Player :public Bace{
private:
public:
	char name[8] = { "null" };//名前
	Point pos{ 0.0f,0.0f };//位置

	//コンストラクタ
	Player(float _x, float _y);//クライアント用
	Player();//サーバー用
	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();

	//初期化
	void Init();
};

//他のプレイヤー
class AnyPlayer :public Bace {
private:
public:
	char name[8] = { "null" };//名前
	Point pos{ 0.0f,0.0f };//位置
	//コンストラクタ
	AnyPlayer(int _id);

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();

};
//弾
class Bullet :public Bace {
private:
public:
	//コンストラクタ
	Bullet(float vx, float vy, float px, float py);

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();
};

