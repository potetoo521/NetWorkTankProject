#pragma once
#include "character.h"
#include "DxFunctionWin.h"



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
int Player::Action(list<unique_ptr<Base>>& base)
{
	//キー入力
	vec.x = 0.0f,vec.y = 0.0f;
	if (CheckHitKey(KEY_INPUT_UP))    vec.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_DOWN))  vec.y =  4.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))  vec.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x =  4.0f;

		//弾丸発射目標取得処理
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		//押された時
		if (mouset_f == false) {//mouseホールド状態確認

			mouset_f = true;//マウス状態

			int x = (int)moupos.x;//int型にキャスト
			int y = (int)moupos.y;

			//mouseカーソルの位置を取得(int型)
			GetMousePoint(&x, &y);

			moupos.x = (float)x; //mouse位置を格納
			moupos.y = (float)y;

			moupos.x = moupos.x - pos.x;//方向ベクトル取得
			moupos.y = moupos.y - pos.y;

			float mag = sqrt(moupos.x * moupos.x + moupos.y * moupos.y);//長さ

			moupos.x = -moupos.x / mag;//正規化方向ベクトル
			moupos.y = -moupos.y / mag;

			//弾丸作成
			Bullet* bullet = new Bullet(pos.x,pos.y,moupos.x, moupos.y);//位置と方向ベクトル
			auto add = (unique_ptr<Base>) bullet;
			base.emplace_back(move(add));//リストにbulletを追加

		}
	}
	else {//押されていない時
		mouset_f = false;
	}


	DrawFormatString(0, 64, GetColor(255, 255, 255),
		"mouse_x:%f          mouse_y:%f"    "pos_x:%d          pos_y:%d",
		moupos.x,
		moupos.y,
		pos.x,
		pos.y
	);

	return 0;
	
}

//描画
void Player::Draw(){

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
