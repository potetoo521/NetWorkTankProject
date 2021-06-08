#pragma once
#include "main.h"



struct MousePos {
	int mouse_x, mouse_y;


};


//プレイヤー
class Player :public Base
{
private:
	int img{ 0 };//画像

public:
	char name[8]{ "null" };//名前
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	MousePos mop{0, 0};  //mouseの位置
	int ID{ -1 };//オブジェクト識別用
	IPDATA ip{ 0,0,0,0 };//IPアドレス保存用

	bool mouset = false;//mouse座標取得判定

	//コンストラクタ
	Player();
	Player(float _x, float _y, char* _name);




	int Action(list<Base*>* base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y);

};

//敵
class Bullet :public Base
{
private:
	int img{ 0 };//画像

public:
	Pos pos{ 0.0f,0.0f };//位置
	Vec vec{ 0.0f,0.0f };//移動ベクトル
	//コンストラクタ
	Bullet(float _x,float _y);

	int Action(list<Base*>* base);
	void Draw();
	bool CheckHit(float m_x, float m_y, float e_x, float e_y) { return 0;};

	


};