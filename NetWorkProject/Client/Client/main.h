#pragma once
#include "DxLib.h"
#include <string.h>
#include <string>
#include <sstream>

#define MAX 2 //接続数
#define MAXBULLET 10 //弾丸数
#define WIDTH 800.0f //windowサイズ 横
#define HEIGHT 600.0f //windowサイズ 縦

#define DESTROY_ID -999 //削除ID

using namespace std;

const int Destroy_ID = -999;//破壊コード
const float B_Speed = 5.0f; //弾丸スピード
const int   B_Bound = 2;    //弾丸bound数
const float P_Speed = 4.0f; //プレイヤースピード

IPDATA IP_set();//IP入力


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
	float x, y;
};

//画像サイズ
struct GraphSize { 
	int x,y; 
};  

//---関数宣言---
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel);//CheckHit関数の宣言

bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y); //ScreenHitCheck関数の宣言

Vec Vector_Plus(Vec a_vec, Vec b_vec);  //ベクトル同士を足す関数

Vec Vector_Minus(Vec a_vec, Vec b_vec); //ベクトル同士を引く関数

Vec Normalize_Vec(Vec vec);             //ベクトルを正規化する関数

Vec Direction_Vec(Pos a_pos, Pos b_pos);//方向ベクトル取得関数

float Vector_Length(Vec vec);           //ベクトルの長さを取得する関数

Pos PosVec_Minus(Pos a_pos, Vec b_vec); //座標とベクトルを足す関数

Pos PosVec_Plus(Pos a_vec, Vec b_vec);  //座標とベクトルを引く関数

bool IsVariable(Pos a_pos);//Pos値が入っているかを判定関数

bool IsVariable(Vec a_pos);//Vec値が入っているかを判定関数


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







