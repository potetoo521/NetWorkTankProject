#pragma once
#include "character.h"
#include "DxFunctionWin.h"

//コンストラクタ
Player::Player(float _x, float _y, char* _name) {
	strcpy_s(name, "null");
	img = LoadGraph("image/maid.png");//画像を読み込み

	GetGraphSize(img, &gr_size.x, &gr_size.y);//画像サイズを取得

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
	if (CheckHitKey(KEY_INPUT_UP))    vec.y = -P_Speed;
	if (CheckHitKey(KEY_INPUT_DOWN))  vec.y =  P_Speed;
	if (CheckHitKey(KEY_INPUT_LEFT))  vec.x = -P_Speed;
	if (CheckHitKey(KEY_INPUT_RIGHT)) vec.x =  P_Speed;

		//弾丸発射目標取得処理
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		//押された時
		if (mouset_f == false) {//mouseホールド状態確認

			mouset_f = true;//マウス状態

			int x = (int)moupos.x;//GetMousePointに入れるためint型にキャスト
			int y = (int)moupos.y;

			GetMousePoint(&x, &y);//mouseカーソルの位置を取得

			moupos.x = (float)x;  //mouse位置を格納
			moupos.y = (float)y;

			mouvec = Normalize_Vec(Direction_Vec(moupos, pos));//方向ベクトルを正規化



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

	//キャラ画像
	DrawGraphF(pos.x, pos.y, img, TRUE);
	
	//名前
	DrawStringF(pos.x,pos.y,
		name,
		GetColor(255, 255, 255)
	);


}
