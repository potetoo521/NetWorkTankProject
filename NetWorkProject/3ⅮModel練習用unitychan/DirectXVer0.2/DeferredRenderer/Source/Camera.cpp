//---------------------------------------------
// Camera.cpp
//---------------------------------------------

#include "Camera.h"
#include "MyInput8.h"
#include "DirectX11Manager.h"
#include "input.h"

#define _TPSCamera
//#define _FPSCamera

#define SCREEN_WIDTH  1270//pixel
#define SCREEN_HEIGHT 760 //pixel
//Camera 設定
#define ViewScope (FLOAT)XM_PI / 3 //180/3=60
#define AspectRatio  SCREEN_WIDTH/SCREEN_HEIGHT
#define NearPlane 0.5f
#define FarPlane  4096 * 2


//--------------------------------------------
// ビューMatrix(視野座標系Matrix）作成
//--------------------------------------------
struct Camera g_camera;

struct Camera* getCamera() {

	return &g_camera;
}

//初期化
void CameraInit() {
	//視点 
	g_camera.eyePos = XMVectorSet(0, 1.5f, -3, 0);//z y x
	
	//注視点
	g_camera.targetPos = XMVectorSet(0, 1.2f, 0, 0);

	//上ベクトル（y軸方向ベクトル）
	g_camera.upVector = XMVectorSet(0, 1, 0, 0);

	//--------------------------------------------
	// ビューMatrix(視野座標系Matrix）作成
	//--------------------------------------------
	g_camera.viewMatrix = XMMatrixLookAtLH(
		g_camera.eyePos, g_camera.targetPos, g_camera.upVector);

	//--------------------------------------------
	//プロジェクションMatrix（透視投影）作成
	//--------------------------------------------
	g_camera.projMatrix = XMMatrixPerspectiveFovLH(
		/*XMConvertToRadians(60.0f),*/
		ViewScope,
		1270.0f / 760.0f, NearPlane, FarPlane);
	
}

void CameraUpdate() {

	//カメラとUnityちゃんの接近を防ぐ







	static int dirflag = 0;

	
	static XMVECTOR vDir=XMVectorSet(0,0,1,1);

	
	//単位ベクトル化
	XMVector4Normalize(vDir);

	
#ifdef _FPSCamera
	//カメラ Bomberman 後方3
	g_camera.eyePos = bpos - vDir * 3;

	//カメラ高さ調整
	
	//ターゲットをBomberman に設定
	g_camera.targetPos = bpos;

#endif
	//移動方向設定

	//if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_LCONTROL))
	//{
	//	dirflag = 2;
	//	g_camera.eyePos += g_camera.viewMatrix.r[3] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
	//	g_camera.targetPos += g_camera.viewMatrix.r[1] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
	//}
	//else if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_LCONTROL))
	//{
	//	dirflag = 2;
	//	g_camera.eyePos -= g_camera.viewMatrix.r[3] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
	//	g_camera.targetPos -= g_camera.viewMatrix.r[1] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	//}
    if (GetKeyboardPress(DIK_DOWN)&& GetKeyboardPress(DIK_LSHIFT))
	{
		dirflag = 1;
		//視点をどっちの方向に動かしますか
		g_camera.eyePos -= g_camera.viewMatrix.r[1] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
		g_camera.targetPos -= g_camera.viewMatrix.r[1] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		dirflag = 1;
		g_camera.eyePos -= g_camera.viewMatrix.r[2] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
		g_camera.targetPos -= g_camera.viewMatrix.r[2] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		dirflag = 1;
		g_camera.eyePos -= g_camera.viewMatrix.r[0] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
		g_camera.targetPos -= g_camera.viewMatrix.r[0] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		dirflag = 1;
		g_camera.eyePos += g_camera.viewMatrix.r[0] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
		g_camera.targetPos += g_camera.viewMatrix.r[0] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	}
	else if (GetKeyboardPress(DIK_UP)&& GetKeyboardPress(DIK_LSHIFT))
	{
		dirflag = 1;
		g_camera.eyePos += g_camera.viewMatrix.r[1] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
		g_camera.targetPos += g_camera.viewMatrix.r[1] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	}
    else if (GetKeyboardPress(DIK_UP))
	{
		dirflag = 1;
		g_camera.eyePos += g_camera.viewMatrix.r[2] * 0.1f;//viewMatrixの3行目　進行方向ベクトル
		g_camera.targetPos += g_camera.viewMatrix.r[2] * 0.1f;//viewMatrixの3行目　進行方向ベクトル

	}
	

	dirflag = 0;//


	//--------------------------------------------
	// ビューMatrix(視野座標系Matrix）作成
	//--------------------------------------------

	g_camera.viewMatrix = XMMatrixLookAtLH(
		g_camera.eyePos, g_camera.targetPos, g_camera.upVector);

}