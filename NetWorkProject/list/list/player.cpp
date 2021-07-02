#pragma once
#include "character.h"

//コンストラクタ
Player::Player() {
	ID = 0;
  	img = LoadGraph("image/maid.png");

	GetGraphSize(img, &gr_size.x, &gr_size.y);//画像サイズを取得

	//gr_size.x = gr_size.x / 2;//画像サイズ半
	//gr_size.y = gr_size.y / 2;
	pos.x = 100.0f;//テスト
	pos.y = 100.0f;

	SetMouseDispFlag(FALSE);//マウス表示なし

	//sound = LoadSoundMem("sound/ES_SomethingGood.wav");
}

//処理
//int Player::Action(list<Base*>* base) {
int Player::Action(list<unique_ptr<Base>>& base) {
	//キー入力
	Vec v{ 0.0f,0.0f };
	if (CheckHitKey(KEY_INPUT_UP))    v.y = -P_Speed;
	if (CheckHitKey(KEY_INPUT_DOWN))  v.y =  P_Speed;
	if (CheckHitKey(KEY_INPUT_LEFT))  v.x = -P_Speed;
	if (CheckHitKey(KEY_INPUT_RIGHT)) v.x =  P_Speed;

	//弾丸発射目標取得処理
	if (GetMouseInput() & MOUSE_INPUT_LEFT) {

		//押された時
		if (mouset_f == false) {//mouseホールド状態確認

			mouset_f = true;//マウス状態

			int x = (int)moupos.x;
			int y = (int)moupos.y;

			GetMousePoint(&x, &y);//mouseカーソルの位置を取得
			
			moupos.x = (float)x;  //mouse位置を格納
			moupos.y = (float)y;

			mouvec = Normalize_Vec(Direction_Vec(moupos, pos));//方向ベクトルを正規化

			//弾丸作成
			Bullet* bullet = new Bullet(pos.x, pos.y, mouvec.x, mouvec.y,ID);//位置と方向ベクトル
			auto add = (unique_ptr<Bullet>) bullet;
			base.emplace_back(move(add));//リストにbulletを追加

		}
	}
	else {//押されていない時
		mouset_f = false;
	}

	if (CheckHitKey(KEY_INPUT_SPACE)) {//デバッグ用bullet削除

		for (auto i = base.begin(); i != base.end(); i++) {
			if (((Bullet*)(*i).get())->ID == 1)
			{
				i = base.erase(i);
				if (i == base.end())break;
			}
		}
	}

	//画面外当たり判定
	ScreenHitCheck(&pos.x, &pos.y,gr_size.x,gr_size.y);

	//移動ベクトルを加算
	pos.x += v.x;
	pos.y += v.y;

	return 0;
}

//描画
void Player::Draw() {
	
	int mx = 0, my = 0;//マウス位置
	GetMousePoint(&mx, &my);

	DrawLine(pos.x, pos.y, mx, my,GetColor(0,0,255));//線を描画


	float len = sqrtf( pos.x *  pos.x +  pos.y * pos.y);//内積の長さを取得
//	DrawCircle(pos.x, pos.y, sqrtf(pos.x * pos.x + pos.y * pos.y), GetColor(255, 0, 0), TRUE);


	//マウス位置を表示
	DrawCircle(mx , my, sqrtf(40), GetColor(255, 0, 0), TRUE);

	//画像表示
	DrawGraphF(pos.x, pos.y, img, TRUE);
}




//
////マウスの位置を取得
//if (flag == true)
//{
//	m_mou_bx = (float)Input::GetPosX();
//	m_mou_by = (float)Input::GetPosY();
//
//	bx = (m_mou_bx - m_bx) * m_vx;
//	by = (m_by - m_mou_by) * m_vy;
//
//	flag = false;
//}
//
//float r = 0.0f;
//r = bx * bx + by * by;
//r = sqrt(r);//r をルートを求める
//
////長さが0かどうか調べる
//if (r == 0.0f)
//{
//	;//0なら何もしない
//}
//else
//{
//	//正規化を行う
//	m_vx = 1.0f / r * bx;
//	m_vy = 1.0f / r * by;
//}