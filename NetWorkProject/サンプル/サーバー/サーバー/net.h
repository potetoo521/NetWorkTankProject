#pragma once
#include "chara.h"

enum {
	T1,//スレッド１
	T2,//スレッド2
	T3,//スレッド3
	T4,//スレッド4
	TAMA//弾
};

//プレイヤーのデータ
typedef struct Player_Data {
	Player p_data[MAX];
	Vec tama_vec[MAX]{ {0.0f,0.0f}, {0.0f,0.0f}, {0.0f,0.0f}, {0.0f,0.0f} };//弾の移動ベクトル
	IPDATA IP[MAX] = { {0,0,0,0},{0,0,0,0},{0,0,0,0},{0,0,0,0} };
	int NetHandle[MAX] = { -1, -1, -1, -1 };//ネットハンドル
	int flg[MAX] = { -1,-1,-1,-1 };//存在の有無(1以上存在)
}Player_Data;


//送信用データ
class SEND_SERVER_DATA{
private:
public:
	int flg[MAX] = { -1,-1,-1,-1 };//存在の有無(1以上存在)
	Point pos[MAX];//プレイヤーの位置
	Vec B_vec[MAX];//弾の移動ベクトル
};

//クライアント用
class  SEND_CLIENT_DATA{
private:
public:
	Point pos[MAX];//プレイヤーの位置
	Vec m_vec{ 0.0f,0.0f };//弾の移動ベクトル
};