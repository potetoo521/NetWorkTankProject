#pragma once
#include "DxLib.h"
#include <list>
#include <memory>

#include "main.h"

using namespace std;

//ベースクラス
class Base {
private:
public:
	int ID{ -1 };//オブジェクトのID
	virtual int Action(list<unique_ptr<Base>>& base) = 0;//処理
	virtual void Draw() = 0;//描画
	//virtual bool CheckHit(float m_x, float m_y, float e_x, float e_y) = 0;

};

//プレイヤー
class Player :public Base
{
private:
	int img{ 0 };//画像

public:
	char name[8]{ "null" };  //名前
	Pos pos{ 0.0f,0.0f };    //位置
	Vec vec{ 0.0f,0.0f };    //移動ベクトル
	Pos moupos{0, 0};        //mouseの位置
	Vec mouvec{ 0,0 };       //mouseベクトル
	GraphSize gr_size{ 0,0 };//画像サイズ
	int ID{ -1 };            //オブジェクト識別用
	IPDATA ip{ 0,0,0,0 };    //IPアドレス保存用

	bool mouset_f = false;   //mouse座標取得判定

	//コンストラクタ
	Player();
	Player(float _x, float _y, char* _name);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y);

};

//送受信データ用のクラス
class SendData{
private:
public:

	Player player[MAX];
	//Bullet bullet[MAXBULLET];
};


//弾丸
class Bullet :public Base
{
private:
	int img{ 0 };//画像

public:
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	GraphSize gr_size{ 0,0 };//画像サイズ
	int owner_Id = -1;//作成元のオブジェクトID格納用
	int boundNum = 0; //弾丸の跳ね返り回数
	//コンストラクタ
	Bullet(float _x, float _y, float _vx, float _vy, int id);

	int Action(list<unique_ptr<Base>>& base);
	void Draw();
	//bool CheckHit(float m_x, float m_y, float e_x, float e_y);

	


};

//
////弾丸
//class BulletData {
//private:
//public:
//
//	Pos pos{ 0.0f,0.0f };//位置
//	Vec vec{ 0.0f,0.0f };//移動ベクトル
//	//コンストラクタ
//	BulletData();
//	BulletData(float _x, float _y);
//	//初期化メソッド
//	void Data_Init();
//
//
//};




