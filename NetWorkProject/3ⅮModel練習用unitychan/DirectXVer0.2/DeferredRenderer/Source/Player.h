#pragma once
#include "UnityExportModel.h"
#include "UnityExportSkinnedModel.h"

#include <DirectXMath.h>

using namespace DirectX;

class Player {
private:

	//Player Transform　データ
	XMVECTOR Pos;//位置
	//XMVECTOR Speed;//速度
	FLOAT Speed;
	XMVECTOR Dir; //方向ベクトル
	FLOAT Yaw;//y軸周り回転角

	//Player Matrix定義
	XMMATRIX WorldMatrix;//World Matix
	XMMATRIX ScaleMatrix;
	XMMATRIX RotationYMatrix;//回転Matrix
	XMMATRIX TranslationMatrix;//移動Matrix

	//移動フラッグ
	int moveflag;

	//Player Animation 制御変数（コントローラー）
	float animeTime;//= 0.0f;
	float animeMaxTime;// = unichanrun.GetMaxAnimationTime();

public:
	Player() {};
	~Player() {};
	
	//ゲッター関数
	//2021-07-12 月曜日
	XMVECTOR GetPos(){ return Pos; }//位置情報取得用
	void SetPos(XMVECTOR setPos) { Pos = setPos; }//位置設定用


	//--------------------------------------------
	// OBB Var Area
	//--------------------------------------------
	XMFLOAT3 maxpos = XMFLOAT3(0, 0, 0);
	XMFLOAT3 minpos = XMFLOAT3(0, 0, 0);


	struct OBB {
		XMMATRIX m_WorldMatrix;
		XMVECTOR m_Pos;              // 位置
		XMVECTOR m_NormaDirect[3];   // 方向ベクトル
		FLOAT m_fLength[3];          // 各軸方向の長さ
	} obb;

	//各種関数
	void PlayerInit();
	void PlayerUninit();

	void PlayerUpdate();

	void PlayerJump();//ジャンプ関数を追加

	void PlayerAnimation();
	
	//2021-.7-12 月曜日
	//引数 距離 BoxPos PlayerPos Box長さ Player長さ
	bool PlayerHit(XMFLOAT3 p_pos, XMFLOAT3 b_pos,float p_len,float b_len); //Boxとの当たり判定 
					  //当たった時、true 
					  //当たってない時、false

	void PlayerDraw();

	
};


class Player* GetPlayer();