//---------------------------------------------
// Unitychan 
// 2021-06-27 Sunday
//---------------------------------------------
#include "Player.h"
#include "input.h"//w,s,d,a

#include "OBB.h" //当たり判定の上級者向けバウンディングボックス
//#include "DirectXMath.h"
//#include "DirectXCollision.h"

//Loader
//---------------------------------------------
// Unitychan Model 定義
// Skin Mesh Animation Model
// Run & Jump
//---------------------------------------------

UnityExportSkinnedModel unitychan;//静止モデル
//-----------------------------------------
// アニメーションパターン定義
//-----------------------------------------
uem::SkinnedAnimation unitychanRunAnime;//走るアニメーション


//GPUに転送する定数バッファ
extern ConstantBufferMatrix consBufferMatrix;
extern ConstantBuffer cbuffer;

class Player* GetPlayer() {

	static class Player g_player;

	return &g_player;

}

//モデルローダー,
//アニメーション　ローダ
void Player::PlayerInit() {

	unitychan.LoadBinary(//本来ならusb
		"Assets/Models/SkinnedMeshData.txt.bin");

	//-----------------------------------------
	// Running　アニメーション
	//-----------------------------------------
	unitychanRunAnime.LoadBinary(//本来なら、anime.com
		"Assets/Models/RUN00_Fanim.bin",
		unitychan.uemData.root.get());//腰の位置にルートボーンがある

	
	//-----------------------------------------
	// Player 回転　設定
	//-----------------------------------------
	Yaw = 0.0f;//ラジアン Y軸 3.14 180度

	XMConvertToRadians(1);
	float radian = (FLOAT)XM_PI / 180;//0.01 約 1度
	
	//-----------------------------------------
	// Player 位置　方向　設定
	//-----------------------------------------

	Pos = XMVectorSet(1, 0.6f, 1, 0);//x,y,z,w
	
	WorldMatrix = XMMatrixIdentity();//単位行列
									 //1 0 0 0
									 //0 1 0 0
									 //0 0 1 0
									 //0 0 0 1
	
	Dir = XMVectorSet(0, 0, 1, 1);//(x y z w)
		

	//--------------------------------------------
	// フォーメーションセット(姿勢制御）
	//--------------------------------------------
	unitychanRunAnime.SetTransform(animeTime);//アニメーションをスタートさせる位置時間を指定
	
	//アニメーションの最大時間を取得
	animeMaxTime = //0.8sec
		unitychanRunAnime.GetMaxAnimationTime();
	
	animeTime = 0.01f;

	//2021-07-12 月曜日
	maxpos = unitychan.maxPos;
	minpos = unitychan.minPos;
}

//解放
void Player::PlayerUninit() {

	


}

//PlayerとBoxの当たり判定
bool Player::PlayerHit(XMFLOAT3 p_pos, XMFLOAT3 b_pos, float p_len, float b_len) {

	//距離 unitychanとBoxの距離


	float distx = (p_pos.x - b_pos.x);//横
	float disty = (p_pos.y - b_pos.y);//縦
	float distz = (p_pos.z - b_pos.z);//奥

	//ピタゴラスの定理
	//平方根　4 の平方根 2 
	//sqrt 平方根
	float dist = sqrtf(distx * distx + disty * disty + distz * distz);

	//長さ　unitychannとBoxの半径 p_len(max.z-min.z)/2  b_len(max.z-min.z)/2
	float len = p_len + b_len;

	//めりこんでいるか
	if (dist <= len) {
	    return true;//当たっている
    }
		return false;//当たっていない

}



void Player::PlayerJump() {

	//位置=位置 + 速度 * 時間
	//速度=初速 + 加速度 * 時間
	//上にジャンプ、下に落ちる9.8f重量加速度
	//G下に加速

	//フラグで状態遷移を管理
	static int jumpflag = 0;

	float G = 0.098f;//約1

	static float fcnt = 0;//フレームカウンタ

	fcnt+=0.01f;//時間が経過している

	//Spaceキーでジャンプ
	if (GetKeyboardPress(DIK_SPACE) && jumpflag == 0) {

		jumpflag = 1;
		Speed = 0.2f- G * fcnt ;

		Pos += XMVectorSet(0, Speed, 0, 0);
		//Pos.m128_f32[2] += Speed;
	}
	else{
		jumpflag = 0;
		fcnt = 0;
		//Speed += Speed - G * fcnt;
	}
	Speed = 0.12f - G;
	Pos -= XMVectorSet(0, Speed, 0, 0);
	
}

//更新
void Player::PlayerUpdate() {
	
	//-------------------------------------
	// Player Motion
	//-------------------------------------
	//約一度　ラジアンで定義　0.01f
	static float radian = (float)XM_PI / 180;
	XMFLOAT3 vPos;//位置
	XMFLOAT3 vRot;//回転
	//回転　Y軸周り
	
	if (GetKeyboardPress(DIK_D))
	{
		Yaw += 0.05f;//約 1°
		//Pos -= Dir * 0.05f;
	}
	if (GetKeyboardPress(DIK_A))
	{
		Yaw -= 0.05f;//約 1°
	}
	

	static bool b_rot=false;
	//進行方向に進む
	//z軸奥はプラス z>0、手前はマイナスz<0
	//モニタースクリーンの位置は z=0
	if (GetKeyboardPress(DIK_W))
	{
		Pos -= Dir * 0.05f;//方向に0.01をかける

	}
	if (GetKeyboardPress(DIK_S))
	{
	    Pos += Dir * 0.05f;//方向に0.01をかける
	}
	
	//Dir=XMQuaternionRotationAxis(Dir,Yaw);
	//Dir=XMQuaternionRotationNormal(Dir, Yaw);
	//Dir=XMQuaternionConjugate(Dir);
	//XMVECTOR rot=XMQuaternionRotationRollPitchYawFromVector(Dir);
	//XMStoreFloat3(&vRot, rot);

	


	//進行方向に進む
	//-------------------------------------
	// Player Motion更新
	//-------------------------------------
	
	//XMVECTORをXMFLOAT3に変換
	//float x,float y,float zを取り出すことができる
	XMStoreFloat3(&vPos, Pos);

	//0.0
	if (vPos.y < -0.0f)
	{
		vPos.y = 0.0f;
	}

	//unitychan WorldMatrix合成
	//回転Matrix * 移動Matrix
	WorldMatrix = XMMatrixRotationY(Yaw) *
		XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
	//unitychan 方向ベクトル設定
	//ローカル座標軸　z軸方向
	
	Dir = WorldMatrix.r[2];//Z軸
	
}


//アニメーション
void Player::PlayerAnimation() {
	
	if (animeTime < animeMaxTime) {
	
		animeTime += 0.01f;

		unitychanRunAnime.SetTransform(animeTime);
	}
	else {

		animeTime = 0.0f;

	}

	
}

//描画
void Player::PlayerDraw() {

	
	//ImGui::Text("やっと、はしれるよ");
	
	//-------------------------------------
	//　Unityちゃんの表示
	//-------------------------------------

	//転置行列　定数バッファに設定
	consBufferMatrix.world = XMMatrixTranspose(
		WorldMatrix);

	

	//GPUに定数バッファ（UnityちゃんのWorld Matrix)を転送
	g_DX11Manager.UpdateConstantBuffer(
		cbuffer.Get(), consBufferMatrix);
	
	//スキンメッシュアニメーション model 表示
	//走るRun Motion

	unitychan.Draw();
	
	
}