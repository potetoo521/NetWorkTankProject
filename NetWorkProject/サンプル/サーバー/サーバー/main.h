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

IPDATA IP_set();//IP入力

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
}Pos;


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

//ベースクラス（弾で使用）
class Bace {
private:
public:
	int img{ -1 };//画像データ
	char ID{ -1 };

	Point pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル

	virtual int Action(list<unique_ptr<Bace>>& bace) = 0;
	virtual void Draw() = 0;
};
