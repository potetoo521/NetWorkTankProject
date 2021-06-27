#pragma once
#include "main.h"


//ベースクラス
class Base {
private:
public:
	int ID{ -1 };//オブジェクトのID
	virtual int Action(list<unique_ptr<Base>>& base) = 0;
	//virtual int Action(list<Base*>* base) = 0;//処理
	virtual void Draw() = 0;//描画

};

//プレイヤー
class Player :public Base
{
private:
	int img{ 0 };//画像
	int sound{ -1 };//サウンド
public:
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	MousePos moupos{ 0, 0 };  //mouseの位置
	GraphSize gr_size{ 0,0 };//画像サイズ
	bool mouset_f =false;
	//コンストラクタ
	Player();
	
	int Action(list<unique_ptr<Base>>& base);
	//int Action(list<Base*>* base);
	void Draw();
	

};

//敵
class Enemy :public Base
{
private:
	int img{ 0 };//画像

public:
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	

	//コンストラクタ
	Enemy(float _x,float _y);

	int Action(list<Base*>* base);
	void Draw();
	
	


};

//弾丸
class Bullet :public Base
{
private:
	int img{ 0 };//画像

public:
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	GraphSize gr_size{ 0,0};//画像サイズ
	int owner_Id = -1;//作成元のオブジェクトID格納用
	int boundNum = 0; //弾丸の跳ね返り回数
	//コンストラクタ
	Bullet(float _x, float _y, float _vx, float _vy,int id);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();

	Pos posd{ 0.0f,0.0f };//位置//デバッグ
};