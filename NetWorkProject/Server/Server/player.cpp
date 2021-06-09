#pragma once
#include "main.h"

//コンストラクタ
PlayerData::PlayerData(float _x, float _y, char* _name) {
	pos.x = _x;
	pos.y = _y;

	strcpy_s(name, _name);
}

//イニシャライズ(初期化)
void PlayerData::Data_Init() {
	strcpy_s(name, "null");

	ip.d1 = 0; ip.d2 = 0; ip.d3 = 0; ip.d4 = 0;

	pos.x = 0.0f;
	pos.y = 0.0f;

	ID = -1;

}

PlayerData::PlayerData() {}

//Action実行
int PlayerData::Action(list<unique_ptr<Base*>>& data) {

	return 0;
}





////描画(サーバー側では描画はしない)
//void Player::Draw() {
//
//}
//

//CheckHit関数の定義
//float m_x = オブジェクトAの X 座標
//float m_y = オブジェクトAの Y 座標

//float e_x = オブジェクトBの X 座標
////float e_y = オブジェクトBの Y 座標
//bool Player::CheckHit(float m_x, float m_y, float e_x, float e_y)
//{
//
//	float len = sqrt((e_x - m_x) * (e_x - m_x) + (e_y - m_y) * (e_y - m_y));
//
//
//
//	if (len <= 32)//32 == 中心までの距離
//	{
//
//		return true;//判定結果当たっている( 真 )を返す
//	}
//	else
//	{
//		return false;//判定結果当たっていない( 偽 )を返す
//	}
//}
