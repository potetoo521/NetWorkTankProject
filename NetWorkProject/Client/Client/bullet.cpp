#pragma once
#include "character.h"

//コンストラクタ
Bullet::Bullet(float _x, float _y) {
	img = LoadGraph("image/hitokage.png");

	ID = 1;
	vec.x = 4.0f + _x;
	vec.y = 4.0f + _y;
}

//処理
int Bullet::Action(list<Base*>* base) {

	////移動ベクトルを加算
	//pos.x += vec.x;
	//pos.y += vec.y;

	////画面の端に来たら、移動ベクトルを逆にする
	//if (pos.x < 0 || pos.x>736.0f)vec.x = -vec.x;
	//if (pos.y < 0 || pos.y>546.0f)vec.y = -vec.y;

	//if (pos.x < 0 || pos.x>736.0f)ID=-999;
	//if (pos.y < 0 || pos.y>546.0f)ID=-999;
	return 0;
}

//描画
void Bullet::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}
