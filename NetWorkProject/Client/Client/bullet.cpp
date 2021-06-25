#pragma once
#include "character.h"

//コンストラクタ
Bullet::Bullet(float _x, float _y,float _vx,float _vy) {
	img = LoadGraph("image/hitokage.png");

	ID = 3;
	pos.x = _x;//出現位置
	pos.y = _y;

	vec.x = _x;//方向ベクトル
	vec.y = _y;
}

//処理
int Bullet::Action(list<unique_ptr<Base>>& base) {

	////移動ベクトルを加算
	pos.x += vec.x;
	pos.y += vec.y;

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





//Objectをマウスクリックポイントの位置に移動させる
//float m_bx    オブジェクトの座標 X
//float m_by    オブジェクトの座標 Y
//float* bx     オブジェクトのベクトル X
//float* by     オブジェクトのベクトル Y
//float speed   移動させる速さ
////float flag    ワンクリック取得フラグ
//void MousePointBullet(float m_bx, float m_by, float* bx, float* by, float speed, bool* flag)
//{
//	float m_mou_bx;//mouse情報保存
//	float m_mou_by;
//	//マウスの位置を取得
//	if (*flag == true)
//	{
//	//	m_mou_bx = (float)Input::GetPosX();
//	//	m_mou_by = (float)Input::GetPosY();
//
//		//*bx = (m_mou_bx - m_bx) * speed;
//		//*by = (m_by - m_mou_by) * speed;
//
//
//		*flag = false;
//	}
//
//	float r = 0.0f;//長さを保存
//	r = (*bx) * (*bx) + (*by) * (*by);
//	r = sqrt(r);//r をルートを求める
//
//	//長さが0かどうか調べる
//	if (r == 0.0f)
//	{
//		;//0なら何もしない
//	}
//	else
//	{
//		//正規化を行う
//		*bx = 1.0f / r * (*bx);
//		*by = 1.0f / r * -(*by);
//	}
//}