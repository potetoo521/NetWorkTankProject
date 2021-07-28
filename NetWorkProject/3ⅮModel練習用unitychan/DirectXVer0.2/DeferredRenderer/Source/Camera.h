//---------------------------------------------
// Camera.h
//---------------------------------------------
#pragma once
#include <DirectXMath.h>

using namespace DirectX;

struct Camera {

	XMVECTOR eyePos;//���_
	XMVECTOR targetPos;//�����_
	XMVECTOR upVector;//��x�N�g��

	XMMATRIX viewMatrix;//View Matix 
	XMMATRIX projMatrix;//Projection Matrix
};

void CameraInit();

void CameraUpdate();

struct Camera* getCamera();