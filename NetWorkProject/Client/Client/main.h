#pragma once
#include "DxLib.h"
#include "character.h"

#include <list>

#include <string.h>
#include <string>
#include <sstream>

#define MAX 4 //接続数
#define WIDTH 800 //windowサイズ 横
#define HEIGHT 600 //windowサイズ 縦

#define DESTROY_ID -999 //削除ID

using namespace std;

IPDATA IP_set();//IP入力

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
/*
//プレイヤークラス
class Data {
private:
public:
	char name[8]{ "null" };//名前
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	int ID{ -1 };//オブジェクト識別用
	IPDATA ip{ 0,0,0,0 };//IPアドレス保存用
	//コンストラクタ
	Data();
	Data(float _x, float _y, char* _name);
	//初期化用メソッド
	void Data_Init();
};*/

//送受信データ用のクラス
class SendData {
private:
public:
	Player data[MAX];
	BulletData b_data[MAX];

};


#define WIDTH 800
#define HEIGHT 600

struct Pos { float x; float y; };//位置

struct Vec { float x; float y; };//移動ベクトル

//ベースクラス
class Base {
private:
public:
	int ID{ -1 };//オブジェクトのID
	virtual int Action(list<unique_ptr<Base*>>&base) = 0;//処理
	virtual void Draw() = 0;//描画
	virtual bool CheckHit(float m_x, float m_y, float e_x, float e_y) = 0;

};





