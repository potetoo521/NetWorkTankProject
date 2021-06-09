#pragma once
#include "character.h"

//コンストラクタ
Player::Player(float _x, float _y, char* _name) {
	strcpy_s(name, "null");
	ID = 0;
	img = LoadGraph("image/maid.png");
	mouset_f = false;//mouse座標取得判定
	ip.d1 = 0; ip.d2 = 0; ip.d3 = 0; ip.d4 = 0;//IPアドレス

	strcpy_s(name, _name);
}

Player::Player(){}

//処理
int Player::Action(list<unique_ptr<Base*>>&base) {
	//キー入力
	Vec v{ 0.0f,0.0f };
	if (CheckHitKey(KEY_INPUT_UP)) v.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_DOWN)) v.y = 4.0f;
	if (CheckHitKey(KEY_INPUT_LEFT)) v.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) v.x = 4.0f;
	

		//弾丸発射目標取得処理
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//押された時
		mouset_f = true;

		//mouseカーソルの位置を取得
		mouset_f = GetMousePoint(&moupos.mouse_x, &moupos.mouse_y);

	}
	else {
		mouset_f = false;
	}
	return 0;
}

//描画
void Player::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}





//CheckHit関数の定義
//float m_x = オブジェクトAの X 座標
//float m_y = オブジェクトAの Y 座標

//float e_x = オブジェクトBの X 座標
//float e_y = オブジェクトBの Y 座標
bool Player::CheckHit(float m_x, float m_y, float e_x, float e_y)
{

	float len = sqrt((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));



	if (len <= 32)//32 == 中心までの距離
	{

		return true;//判定結果当たっている( 真 )を返す
	}
	else
	{
		return false;//判定結果当たっていない( 偽 )を返す
	}

}
