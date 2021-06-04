#pragma once
#include "DxLib.h"

#include <string.h>
#include <string>
#include <sstream>

#define MAX 2 //接続数
#define WIDTH 800 //windowサイズ 横
#define HEIGHT 600 //windowサイズ 縦

//IPDATA IP_set();//IP入力

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
struct Point {
	float x, y;
};

//mouseの位置情報
struct MousePos {
	int x, y;
};


//プレイヤークラス
class Data {
private:
public:
	char name[8]{ "null" };//名前
	Point pos{ 0.0f,0.0f };//位置
	MousePos mouPos{ 0,0 };//mouseの位置

	int ID{ -1 };//オブジェクト識別用
	IPDATA ip{ 0,0,0,0 };//IPアドレス保存用
	//コンストラクタ
	Data();
	Data(float _x, float _y, char* _name);
	//初期化用メソッド
	void Data_Init();
};

class BulletData {
private:
public:

	Point pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	//コンストラクタ
	BulletData();
	BulletData(float _x, float _y);
	//初期化メソッド
	void Data_Init();


};



//送受信データ用のクラス
class SendData {
private:
public:
	Data data[MAX];
	BulletData b_data[MAX];
};












