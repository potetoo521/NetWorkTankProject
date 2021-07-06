#pragma once
#include "main.h"

//マウスクラス
class Mouse {
private:
public:
	int img{ -1 };//画像
	float rad{ 0.0f };//描画する時の角度
	Point pos{ 0.0f,0.0f };
	Vec v{ 0.0f,0.0f };//移動ベクトル
	Vec b_v{ 0.0f,0.0f };//弾の移動ベクトル

	int button_push{ 0 };//ボタン制御

	//コンストラクタ
	Mouse();

	int Action(list<unique_ptr<Bace>>& bace, float px, float py);//ボタンの状態を返す。(プレイヤーのx座標,プレイヤーのy座標)

	void Drwa();
};
