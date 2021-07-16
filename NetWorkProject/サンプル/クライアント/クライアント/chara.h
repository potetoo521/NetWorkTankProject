#pragma once
#include "main.h"

//プレイヤー
class Player :public Bace{
private:
public:
	char name[8] = { "null" };//名前
	Point pos{ 0.0f,0.0f };//位置
	bool hit_flag = false;    //弾丸のヒット判定フラグ

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

	Vec bullet_vec{ 0.0f,0.0f };//弾の移動ベクトル
	Pos bullet_pos{ 0.0f,0.0f };//弾の位置
	bool hit_flag = false;    //弾丸のヒット判定フラグ

	//コンストラクタ
	Bullet(float vx, float vy, float px, float py,char id);
	Bullet();

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();
};

