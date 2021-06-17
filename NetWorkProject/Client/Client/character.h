#pragma once
#include "DxLib.h"
#include <list>
#include <memory>
#include <string.h>
#include <string>
#include <sstream>
using namespace std;

//移動ベクトル
struct Vec {
	float x, y;
};

//位置情報
struct Pos {
	float x, y;
};

//mouse位置を取得
struct MousePos {
	float x,y;
};

//ベースクラス
class Base {
private:
public:
	int ID{ -1 };//オブジェクトのID
	virtual int Action(list<unique_ptr<Base>>& base) = 0;//処理
	virtual void Draw() = 0;//描画
	//virtual bool CheckHit(float m_x, float m_y, float e_x, float e_y) = 0;

};

//プレイヤー
class Player :public Base
{
private:
	int img{ 0 };//画像

public:
	char name[8]{ "null" }; //名前
	Pos pos{ 0.0f,0.0f };   //位置
	Vec vec{ 0.0f,0.0f };   //移動ベクトル
	MousePos moupos{0, 0};  //mouseの位置
	int ID{ -1 };           //オブジェクト識別用
	IPDATA ip{ 0,0,0,0 };   //IPアドレス保存用

	bool mouset_f = false;  //mouse座標取得判定

	//コンストラクタ
	Player();
	Player(float _x, float _y, char* _name);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y);

};

//弾丸
class Bullet :public Base
{
private:
	int img{ 0 };//画像

public:
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	//コンストラクタ
	Bullet(float _x,float _y,float _vx,float _vy);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	//bool CheckHit(float m_x, float m_y, float e_x, float e_y);

	


};

//
////弾丸
//class BulletData {
//private:
//public:
//
//	Pos pos{ 0.0f,0.0f };//位置
//	Vec vec{ 0.0f,0.0f };//移動ベクトル
//	//コンストラクタ
//	BulletData();
//	BulletData(float _x, float _y);
//	//初期化メソッド
//	void Data_Init();
//
//
//};




