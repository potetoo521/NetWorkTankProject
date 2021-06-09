#pragma once
#include "DxLib.h"

#include <memory>
#include <string.h>
#include <string>
#include <sstream>
#include <list>

#define MAX 2 //接続数
#define WIDTH 800 //windowサイズ 横
#define HEIGHT 600 //windowサイズ 縦

//IPDATA IP_set();//IP入力
using namespace std;

//スレッドのナンバー
enum {
	T_A,
	T_B,
	T_C,
	T_D
};

//移動ベクトル
struct Vec {
	float x, y;
};

//位置情報
struct Pos {
	float x, y;
};

//mouseの位置情報
struct MousePos {
	int x, y;
};


//ベースクラス
class Base {
private:
public:
	int ID{ -1 };//オブジェクトのID
	virtual int Action(list<unique_ptr<Base*>>& base) = 0;//処理
	virtual void Data_Init()=0;//初期化用
	//virtual void Draw() = 0;//描画
	//virtual bool CheckHit(float m_x, float m_y, float e_x, float e_y) = 0;

};

//プレイヤークラス
class PlayerData :public Base{
private:
	int img{0};
public:
	char name[8]{ "null" };//名前
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	MousePos moupos{ 0, 0 };  //mouseの位置
	int ID{ -1 };//オブジェクト識別用
	IPDATA ip{ 0,0,0,0 };//IPアドレス保存用

	bool mouset_f = false;//mouse座標取得判定

	//コンストラクタ
	PlayerData();
	PlayerData(float _x, float _y, char* _name);

	int Action(list<unique_ptr<Base*>>& data);

	//初期化用メソッド
	void Data_Init();

	//処理
	//int Player::Action(list<Base*>* base) {
	//void Draw();
	
};


class BulletData :public Base{
private:
public:

	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	//コンストラクタ
	BulletData();
	BulletData(float _x, float _y);

	
	int Action(list<unique_ptr<Base*>>& base);
	//初期化メソッド
	void Data_Init();


};

//送受信データ用のクラス
class SendData {
private:
public:
	PlayerData data[MAX];
	BulletData b_data[MAX];
};












