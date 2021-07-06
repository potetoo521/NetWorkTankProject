#pragma once
#include "mouse.h"
#include "chara.h"

//コンストラクタ
Mouse::Mouse() {
	img = LoadGraph("image\\mouseArrow.png");
}

//処理
//ボタンの状態を返す。(プレイヤーのx座標,プレイヤーのy座標)
int Mouse::Action(list<unique_ptr<Bace>>& bace, float px, float py) {
	int mx, my;
	GetMousePoint(&mx, &my);//マウスの位置情報取得

	//矢印
	//プレイヤーとマウスの間のベクトルを求める
	v.x = mx - (int)px;
	v.y = my - (int)py;
	float d = sqrtf((px - mx) * (px - mx) + (py - my) * (py - my));//距離を求める
	//描画位置の計算
	//正規化して、プレイヤーから60pixの位置に設定
	pos.x = (v.x / d) * 60 + px;
	pos.y = (v.y / d) * 60 + py;
	//矢印を描画する場合の角度を計算
	rad = atan2((double)pos.x - mx, (double)pos.y - my);

	//マウスのボタンクリックした時
	if ((GetMouseInput() & MOUSE_INPUT_LEFT) != 0 && button_push==0) {
		//飛ばす方向ベクトルを計算
		Vec v;
		v.x = pos.x - px;
		v.y = pos.y - py;
		float d = sqrtf(v.x * v.x + v.y * v.y);
		v.x = (v.x / d) * 4.0f;
		v.y = (v.y / d) * 4.0f;
		//弾を生成
		bace.emplace_back((unique_ptr<Bace>)new Bullet(v.x, v.y, px, py));
		//弾の移動ベクトル
		b_v.x = v.x;
		b_v.y = v.y;

		//ボタンの情報を更新
		button_push = 1;
	}else if((GetMouseInput() & MOUSE_INPUT_LEFT)==0)	//マウス左ボタンを離したら
	{
		//ボタンの情報を更新
		button_push = 0;
	}

	return button_push;
}

void Mouse::Drwa() {
	DrawRotaGraph((int)pos.x + 32, (int)pos.y + 32, 1.0, -rad, img, TRUE);
}
