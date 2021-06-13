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
int Player::Action()
{
	//キー入力
	
	if (CheckHitKey(KEY_INPUT_UP))    vec.y = -4.0f;
	if (CheckHitKey(KEY_INPUT_DOWN))  vec.y =  4.0f;
	if (CheckHitKey(KEY_INPUT_LEFT))  vec.x = -4.0f;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x =  4.0f;

		//弾丸発射目標取得処理
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {
		//押された時

		//mouseカーソルの位置を取得
		GetMousePoint(&moupos.x, &moupos.y);//修正------
			
			float mag = sqrt(moupos.x * moupos.x + moupos.y * moupos.y);

			//正規化方向ベクトル
			moupos.x = moupos.x / mag ;
			moupos.y = moupos.y / mag ;
			
			////方向ベクトルを取得
			//moupos.x = pos.x - moupos.x;
			//moupos.y = pos.y - moupos.y;
			mouset_f = true;//マウス状態

	}
	else {//押されていない時			//moupos.x = 0; moupos.y = 0;
		mouset_f = false;
	}

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
