#pragma once
#include "DxLib.h"
#include <list>
#include <memory>//メモリ解放に必要

using namespace std;

#define WIDTH 1280.0f
#define HEIGHT 980.0f
#define FPS 60

const int Destroy_ID = -999;   //破壊ID
const int B_Bound = 2;         //弾丸のバウンド回数
const float B_Speed = 1.0f;    //弾丸のスピード
const float P_Speed = 4.0f;    //Playerの移動スピード

struct MousePos { float x; float y; };//mouseベクトルを取得

struct GraphSize { int x; int y; };//画像サイズ

struct Pos { float x; float y; };//位置

struct Vec { float x; float y; };//移動ベクトル

//CheckHitDraw関数の宣言
void CheckHitDraw(Pos pos,GraphSize p_pixel);

//CheckHit関数の宣言
bool CheckHit(Pos a_pos, Pos b_pos, GraphSize a_pixel, GraphSize b_pixel);

//ScreenHitCheck関数の宣言
void ScreenHitCheck(Pos* pos, GraphSize gr);
