#pragma once
#include "explosion.h"

//コンストラクタ
Explosion::Explosion(float _x, float _y) {
	//画像データ
	img = LoadGraph("image\\ex.png");

	//描画位置
	pos.x = _x;
	pos.y = _y;

	//切り取り位置
	RectX = 0;
	RectY = 0;

}

//処理
int Explosion::Action(list<unique_ptr<Bace>>& bace) {
	anim_cnt++;

	if (anim_cnt % 8 == 0) {
		RectX += 64;
	}

	if (RectX == 256) {
		RectX = 0;
		RectY += 64;
	}
	if (RectY == 128) FLAG = false;

	return 0;
}

//描画
void Explosion::Draw() {
	DrawRectGraphF(pos.x, pos.y, RectX, RectY, IMGWIDTH64, IMGHEIGHT64, img, true, false);
}
