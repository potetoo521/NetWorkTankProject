#pragma once
#include "DxLib.h"
#include <list>
#include <memory>//メモリ解放に必要

using namespace std;

#define WIDTH 1280.0f
#define HEIGHT 980.0f
#define FPS 60

const int Destroy_ID = -999;//破壊コード
const float B_Speed = 5.0f; //弾丸スピード
const int   B_Bound = 2;    //弾丸bound数
const float P_Speed = 4.0f; //プレイヤースピード

struct GraphSize { int x; int y; };   //画像サイズ

struct Pos { float x; float y; };     //位置

struct Vec { float x; float y; };     //移動ベクトル

//---関数宣言---
bool CheckHit(float m_x, float m_y, float e_x, float e_y, float p_pixel, float e_pixel);//CheckHit関数の宣言

bool ScreenHitCheck(float* x, float* y, int gr_x, int gr_y);//ScreenHitCheck関数の宣言

Vec Vector_Plus(Vec a_vec, Vec b_vec);  //ベクトル同士を足す関数

Vec Vector_Minus(Vec a_vec, Vec b_vec); //ベクトル同士を引く関数

Vec Normalize_Vec(Vec vec);             //ベクトルを正規化する関数

Vec Direction_Vec(Pos a_pos, Pos b_pos);//方向ベクトル取得関数

float Vector_Length(Vec vec);           //ベクトルの長さを取得する関数

Pos PosVec_Minus(Pos a_pos, Vec b_vec); //座標とベクトルを足す関数

Pos PosVec_Plus(Pos a_vec, Vec b_vec);  //座標とベクトルを引く関数