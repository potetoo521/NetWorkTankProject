#include "main.h"


//---関数宣言---
//bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel);//CheckHit関数の宣言
//
//bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y); //ScreenHitCheck関数の宣言
//
//Vec Vector_Plus(Vec a_vec, Vec b_vec);  //ベクトル同士を足す関数
//
//Vec Vector_Minus(Vec a_vec, Vec b_vec); //ベクトル同士を引く関数
//
//Vec Normalize_Vec(Vec vec);             //ベクトルを正規化する関数
//
//Vec Direction_Vec(Pos a_pos, Pos b_pos);//方向ベクトル取得関数
//
//float Vector_Length(Vec vec);           //ベクトルの長さを取得する関数
//
//Pos PosVec_Minus(Pos a_pos, Vec b_vec); //座標とベクトルを足す関数
//
//Pos PosVec_Plus(Pos a_vec, Vec b_vec);  //座標とベクトルを引く関数
//
//bool IsVariable(Pos a_pos);//Pos値が入っているかを判定関数
//
//bool IsVariable(Vec a_pos);//Vec値が入っているかを判定関数


bool IsVariable(Pos a_pos) {

	//変数の中身が入っていれば真
	if (a_pos.x != NULL && a_pos.y != NULL)
	{
		return true;
	}
	else {
		return false;
	}
}

bool IsVariable(Vec a_vec) {

	//変数の中身が0.0fでないまたは、中身が入っていれば真
	if (a_vec.x != NULL && a_vec.y != NULL)
	{
		return true;
	}
	else {
		return false;
	}
}

//方向ベクトル取得用
Vec Direction_Vec(Pos a_pos,Pos b_pos)
{
	Vec vec{ 0,0 };

	vec.x = a_pos.x - b_pos.x;//位置-位置
	vec.y = a_pos.y - b_pos.y;

	return vec;
}

//Vectorの長さを取得
float Vector_Length(Vec vec) {

	float mag = sqrtf(vec.x * vec.x + vec.y * vec.y);//長さを取得

	return mag;
}

//Vectorを正規化
Vec Normalize_Vec(Vec a_vec)
{
	float len = Vector_Length(a_vec);//長さを取得

	a_vec.x = a_vec.x / len;//ベクトルvecとベクトルの長さlenで割る
	a_vec.y = a_vec.y / len;

	return a_vec;
}

//座標とベクトルを足す
Pos PosVec_Plus(Pos a_pos, Vec b_vec)
{
	a_pos.x = a_pos.x + b_vec.x;//位置 + ベクトル
	a_pos.y = a_pos.y + b_vec.y;

	return a_pos;
}

//座標とベクトルを引く
Pos PosVec_Minus(Pos a_pos, Vec b_vec)
{
	a_pos.x = a_pos.x - b_vec.x;//位置 - ベクトル
	a_pos.y = a_pos.y - b_vec.y;

	return a_pos;
}

//ベクトルを足す
Vec Vector_Plus(Vec a_vec, Vec b_vec)
{
	a_vec.x = a_vec.x + b_vec.x;//ベクトル + ベクトル
	a_vec.y = a_vec.y + b_vec.y;

	return a_vec;
}

//ベクトルを引く
Vec Vector_Minus(Vec a_vec, Vec b_vec)
{
	a_vec.x = a_vec.x - b_vec.x;//ベクトル - ベクトル
	a_vec.y = a_vec.y - b_vec.y;

	return a_vec;
}

//当たり判定  画像縦横比(pixel)が一致している場合のみ
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel) {

	float magLen = (p_pixel + e_pixel) / 2;

	float len = sqrtf((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));//内積の長さを取得

	if (len <= magLen)//MagLen == lenまでの距離
	{
		return true;//判定結果当たっている( 真 )を返す
	}
	else
	{
		return false;//判定結果当たっていない( 偽 )を返す
	}
};

//画面の端に来たら画面外に出ない用に位置を修正する
bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y) {

	//x軸
	if (*x + gr_x > WIDTH) {
		*x = WIDTH - gr_x;
		return true;
	}
	if (*x < 0) {
		*x = 0;
		return true;
	}
	//y軸
	if (*y + gr_y > HEIGHT) {
		*y = HEIGHT - gr_y;
		return true;
	}
	if (*y < 0) {
		*y = 0;
		return true;
	}
	return false;
}