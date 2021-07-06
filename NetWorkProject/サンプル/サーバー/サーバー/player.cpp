#pragma once
#include "chara.h"
//プレイヤー

//クライアント用コンストラクタ
Player::Player(float _x,float _y) {
	img = LoadGraph("image\\koiking.png");
	
	pos.x = _x;
	pos.y = _y;
}

//サーバー用コンストラクタ
Player::Player() {

}

//処理
int Player::Action(list<unique_ptr<Bace>>& bace) {
	vec.x = 0.0f; vec.y = 0.0f;

	if (CheckHitKey(KEY_INPUT_W)) vec.y = -4.0f;//上
	if (CheckHitKey(KEY_INPUT_S)) vec.y = 4.0f;//下
	if (CheckHitKey(KEY_INPUT_A)) vec.x = -4.0f;//右
	if (CheckHitKey(KEY_INPUT_D)) vec.x = 4.0f;//左

	pos.x += vec.x;
	pos.y += vec.y;

	if (pos.x < 0.0f) pos.x = 0.0f;
	if (pos.x > 736.0f) pos.x = 736.0f;
	if (pos.y < 0.0f) pos.y = 0.0f;
	if (pos.y > 536.0f) pos.y = 536.0f;

	if (vec.x != 0.0f || vec.y != 0.0f) {
		return 1;
	}
	return 0;
}

//描画
void Player::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}

//初期化
void Player::Init() {
	img = -1;
	strcpy_s(name, "null");
	pos.x = 0.0f;
	pos.y = 0.0f;
}