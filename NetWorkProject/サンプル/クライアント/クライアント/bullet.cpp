#pragma once
#include "chara.h"
//弾

//コンストラクタ
Bullet::Bullet(float vx, float vy,float px,float py,char id) {
	img = LoadGraph("image\\bullet.png");

	pos.x = px+16;
	pos.y = py+16;
	ID = id;
	vec.x = vx;
	vec.y = vy;

	FLAG = true;
}

//処理
int Bullet::Action(list<unique_ptr<Bace>>& bace) {
	pos.x += vec.x;
	pos.y += vec.y;

	//画面外に出たら削除
	if (pos.x<0 || pos.y<0 || pos.x>WIDTH - 32 || pos.y>HEIGHT - 32) {
		FLAG = false;
	}
	if (ID == DESTROY_ID) {
		FLAG = false;
	}

	for (auto a = bace.begin(); a != bace.end(); a++) {//リスト
		Pos p_pos = (*a).get()->pos;
		if (CheckHit(p_pos.x,p_pos.y,pos.x,pos.y,64.0f,64.0f)) {//プレイヤーの位置と弾丸の位置,大きさ
			(*a).get()->FLAG = true;//当たっている
		}
	}


	return 0;
}

//描画
void Bullet::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}

//サーバー用コンストラクタ
Bullet::Bullet() {

}