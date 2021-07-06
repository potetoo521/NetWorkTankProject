#pragma once
#include "chara.h"
//他のプレイヤー

//コンストラクタ
AnyPlayer::AnyPlayer(int _id) {
	img = LoadGraph("image\\hitokage.png");
	ID = _id;

	FLAG = true;
}

//処理
//0:移動する　0以外：移動できない
int AnyPlayer::Action(list<unique_ptr<Bace>>& bace) {
	return -1;
}

//描画
void AnyPlayer::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}