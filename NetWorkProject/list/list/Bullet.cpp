#pragma once
#include "character.h"

//コンストラクタ
Bullet::Bullet(float _x, float _y, float _vx, float _vy,int _id) {

	img = LoadGraph("image/hitokage.png");//画像データをロード

	GetGraphSize(img, &gr_size.x, &gr_size.y);//画像サイズを取得

	posd.x = _x;
	posd.y = _y;

	owner_Id = _id;//作成元objID
	ID = 1;
	pos.x = _x;//出現位置
	pos.y = _y;

	vec.x = _vx;//方向ベクトル
	vec.y = _vy;
}

//処理
int Bullet::Action(list<unique_ptr<Base>>& base) {

	////移動ベクトルを加算
	pos.x += vec.x*B_Speed;
	pos.y += vec.y*B_Speed;
	
	////画面の端に来たら、移動ベクトルを逆にする
	if (pos.x < 0 || pos.x + gr_size.x>WIDTH) {
		vec.x = -vec.x; 
		++boundNum;//bound数更新
	}
	if (pos.y < 0 || pos.y + gr_size.y>HEIGHT){ 
		vec.y = -vec.y;
		++boundNum;
	}

	//跳ね返り上限を超えると削除
	if (boundNum > B_Bound)ID = Destroy_ID;

	//オブジェクトチェック
	for (auto i = base.begin(); i != base.end(); i++) {

		auto data =((Player*)(*i).get());//Playerデータをキャスト
		
		if (data->ID != owner_Id && ID != Destroy_ID && data->ID!=ID){  //作成元オブジェクトではない&破壊中でない

			Pos p_pos{ 0.0f,0.0f }; //位置
			GraphSize p_size{ 0,0 };//画像サイズ

			p_pos  = data->pos;
			p_size = data->gr_size;
			
			//当たり判定
			if (CheckHit( pos.x, pos.y, p_pos.x, p_pos.y, gr_size.x, p_size.x )) {
				ID = Destroy_ID;//リストから削除
			}
			if (i == base.end())break;

		}
	}

	return 0;
}

//描画
void Bullet::Draw() {
	//当たり判定エリア表示
	DrawCircle(pos.x , pos.y , sqrtf(20), GetColor(0, 255, 0), TRUE);

	DrawLine(posd.x , posd.y , pos.x, pos.y, GetColor(255, 100, 255));//線を描画
	//画像描画
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