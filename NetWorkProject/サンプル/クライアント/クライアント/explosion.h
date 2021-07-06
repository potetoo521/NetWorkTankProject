#pragma once
#include "main.h"
//爆発

class Explosion : public Bace {
private:
public:
	int img{ -1 };
	int flag{ -1 };

	Point pos{ 0.0f,0.0f };
	int RectX, RectY;//切り取り位置
	int anim_cnt{ 0 };//アニメーションカウント用

	//コンストラクタ
	Explosion(float _x, float _y);

	int Action(list<unique_ptr<Bace>>& bace);
	void Draw();

};