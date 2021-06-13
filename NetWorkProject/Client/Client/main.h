#pragma once
#include "DxLib.h"
#include "character.h"
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
};






