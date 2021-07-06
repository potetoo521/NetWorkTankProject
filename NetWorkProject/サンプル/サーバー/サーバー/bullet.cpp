#pragma once
#include "chara.h"
//弾

//コンストラクタ
Bullet::Bullet(float vx, float vy,float px,float py) {
	img = LoadGraph("image\\bullet.png");

	pos.x = px+16;
	pos.y = py+16;

	vec.x = vx;
	vec.y = vy;

	ID = 0;
}

//処理
int Bullet::Action(list<unique_ptr<Bace>>& bace) {
	pos.x += vec.x;
	pos.y += vec.y;

	//画面外に出たら削除
	if (pos.x<0 || pos.y<0 || pos.x>WIDTH - 32 || pos.y>HEIGHT - 32) {
		ID = -1;
	}

	return 0;
}

//描画
void Bullet::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}