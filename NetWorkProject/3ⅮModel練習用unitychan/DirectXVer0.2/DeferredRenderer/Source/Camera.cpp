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
//Camera �ݒ�
#define ViewScope (FLOAT)XM_PI / 3 //180/3=60
#define AspectRatio  SCREEN_WIDTH/SCREEN_HEIGHT
#define NearPlane 0.5f
#define FarPlane  4096 * 2


//--------------------------------------------
// �r���[Matrix(������W�nMatrix�j�쐬
//--------------------------------------------
struct Camera g_camera;

struct Camera* getCamera() {

	return &g_camera;
}

//������
void CameraInit() {
	//���_ 
	g_camera.eyePos = XMVectorSet(0, 1.5f, -3, 0);//z y x
	
	//�����_
	g_camera.targetPos = XMVectorSet(0, 1.2f, 0, 0);

	//��x�N�g���iy�������x�N�g���j
	g_camera.upVector = XMVectorSet(0, 1, 0, 0);

	//--------------------------------------------
	// �r���[Matrix(������W�nMatrix�j�쐬
	//--------------------------------------------
	g_camera.viewMatrix = XMMatrixLookAtLH(
		g_camera.eyePos, g_camera.targetPos, g_camera.upVector);

	//--------------------------------------------
	//�v���W�F�N�V����Matrix�i�������e�j�쐬
	//--------------------------------------------
	g_camera.projMatrix = XMMatrixPerspectiveFovLH(
		/*XMConvertToRadians(60.0f),*/
		ViewScope,
		1270.0f / 760.0f, NearPlane, FarPlane);
	
}

void CameraUpdate() {

	//�J������Unity�����̐ڋ߂�h��







	static int dirflag = 0;

	
	static XMVECTOR vDir=XMVectorSet(0,0,1,1);

	
	//�P�ʃx�N�g����
	XMVector4Normalize(vDir);

	
#ifdef _FPSCamera
	//�J���� Bomberman ���3
	g_camera.eyePos = bpos - vDir * 3;

	//�J������������
	
	//�^�[�Q�b�g��Bomberman �ɐݒ�
	g_camera.targetPos = bpos;

#endif
	//�ړ������ݒ�

	//if (GetKeyboardPress(DIK_UP) && GetKeyboardPress(DIK_LCONTROL))
	//{
	//	dirflag = 2;
	//	g_camera.eyePos += g_camera.viewMatrix.r[3] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
	//	g_camera.targetPos += g_camera.viewMatrix.r[1] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
	//}
	//else if (GetKeyboardPress(DIK_DOWN) && GetKeyboardPress(DIK_LCONTROL))
	//{
	//	dirflag = 2;
	//	g_camera.eyePos -= g_camera.viewMatrix.r[3] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
	//	g_camera.targetPos -= g_camera.viewMatrix.r[1] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	//}
    if (GetKeyboardPress(DIK_DOWN)&& GetKeyboardPress(DIK_LSHIFT))
	{
		dirflag = 1;
		//���_���ǂ����̕����ɓ������܂���
		g_camera.eyePos -= g_camera.viewMatrix.r[1] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
		g_camera.targetPos -= g_camera.viewMatrix.r[1] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	}
	else if (GetKeyboardPress(DIK_DOWN))
	{
		dirflag = 1;
		g_camera.eyePos -= g_camera.viewMatrix.r[2] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
		g_camera.targetPos -= g_camera.viewMatrix.r[2] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	}
	else if (GetKeyboardPress(DIK_LEFT))
	{
		dirflag = 1;
		g_camera.eyePos -= g_camera.viewMatrix.r[0] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
		g_camera.targetPos -= g_camera.viewMatrix.r[0] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	}
	else if (GetKeyboardPress(DIK_RIGHT))
	{
		dirflag = 1;
		g_camera.eyePos += g_camera.viewMatrix.r[0] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
		g_camera.targetPos += g_camera.viewMatrix.r[0] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	}
	else if (GetKeyboardPress(DIK_UP)&& GetKeyboardPress(DIK_LSHIFT))
	{
		dirflag = 1;
		g_camera.eyePos += g_camera.viewMatrix.r[1] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
		g_camera.targetPos += g_camera.viewMatrix.r[1] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	}
    else if (GetKeyboardPress(DIK_UP))
	{
		dirflag = 1;
		g_camera.eyePos += g_camera.viewMatrix.r[2] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��
		g_camera.targetPos += g_camera.viewMatrix.r[2] * 0.1f;//viewMatrix��3�s�ځ@�i�s�����x�N�g��

	}
	

	dirflag = 0;//


	//--------------------------------------------
	// �r���[Matrix(������W�nMatrix�j�쐬
	//--------------------------------------------

	g_camera.viewMatrix = XMMatrixLookAtLH(
		g_camera.eyePos, g_camera.targetPos, g_camera.upVector);

}