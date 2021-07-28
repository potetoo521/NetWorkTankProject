//---------------------------------------------
// Camera.h
//---------------------------------------------
#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Camera {

	XMVECTOR eyePos;//視点
	XMVECTOR targetPos;//注視点
	XMVECTOR upVector;//上ベクトル

	XMMATRIX viewMatrix;//View Matix 
	XMMATRIX projMatrix;//Projection Matrix
};

void CameraInit();

void CameraUpdate();

struct Camera* getCamera();