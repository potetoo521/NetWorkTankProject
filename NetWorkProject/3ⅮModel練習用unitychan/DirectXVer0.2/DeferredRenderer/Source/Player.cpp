//---------------------------------------------
// Unitychan 
// 2021-06-27 Sunday
//---------------------------------------------
#include "Player.h"
#include "input.h"//w,s,d,a

#include "OBB.h" //�����蔻��̏㋉�Ҍ����o�E���f�B���O�{�b�N�X
//#include "DirectXMath.h"
//#include "DirectXCollision.h"

//Loader
//---------------------------------------------
// Unitychan Model ��`
// Skin Mesh Animation Model
// Run & Jump
//---------------------------------------------

UnityExportSkinnedModel unitychan;//�Î~���f��
//-----------------------------------------
// �A�j���[�V�����p�^�[����`
//-----------------------------------------
uem::SkinnedAnimation unitychanRunAnime;//����A�j���[�V����


//GPU�ɓ]������萔�o�b�t�@
extern ConstantBufferMatrix consBufferMatrix;
extern ConstantBuffer cbuffer;

class Player* GetPlayer() {

	static class Player g_player;

	return &g_player;

}

//���f�����[�_�[,
//�A�j���[�V�����@���[�_
void Player::PlayerInit() {

	unitychan.LoadBinary(//�{���Ȃ�usb
		"Assets/Models/SkinnedMeshData.txt.bin");

	//-----------------------------------------
	// Running�@�A�j���[�V����
	//-----------------------------------------
	unitychanRunAnime.LoadBinary(//�{���Ȃ�Aanime.com
		"Assets/Models/RUN00_Fanim.bin",
		unitychan.uemData.root.get());//���̈ʒu�Ƀ��[�g�{�[��������

	
	//-----------------------------------------
	// Player ��]�@�ݒ�
	//-----------------------------------------
	Yaw = 0.0f;//���W�A�� Y�� 3.14 180�x

	XMConvertToRadians(1);
	float radian = (FLOAT)XM_PI / 180;//0.01 �� 1�x
	
	//-----------------------------------------
	// Player �ʒu�@�����@�ݒ�
	//-----------------------------------------

	Pos = XMVectorSet(1, 0.6f, 1, 0);//x,y,z,w
	
	WorldMatrix = XMMatrixIdentity();//�P�ʍs��
									 //1 0 0 0
									 //0 1 0 0
									 //0 0 1 0
									 //0 0 0 1
	
	Dir = XMVectorSet(0, 0, 1, 1);//(x y z w)
		

	//--------------------------------------------
	// �t�H�[���[�V�����Z�b�g(�p������j
	//--------------------------------------------
	unitychanRunAnime.SetTransform(animeTime);//�A�j���[�V�������X�^�[�g������ʒu���Ԃ��w��
	
	//�A�j���[�V�����̍ő厞�Ԃ��擾
	animeMaxTime = //0.8sec
		unitychanRunAnime.GetMaxAnimationTime();
	
	animeTime = 0.01f;

	//2021-07-12 ���j��
	maxpos = unitychan.maxPos;
	minpos = unitychan.minPos;
}

//���
void Player::PlayerUninit() {

	


}

//Player��Box�̓����蔻��
bool Player::PlayerHit(XMFLOAT3 p_pos, XMFLOAT3 b_pos, float p_len, float b_len) {

	//���� unitychan��Box�̋���


	float distx = (p_pos.x - b_pos.x);//��
	float disty = (p_pos.y - b_pos.y);//�c
	float distz = (p_pos.z - b_pos.z);//��

	//�s�^�S���X�̒藝
	//�������@4 �̕����� 2 
	//sqrt ������
	float dist = sqrtf(distx * distx + disty * disty + distz * distz);

	//�����@unitychann��Box�̔��a p_len(max.z-min.z)/2  b_len(max.z-min.z)/2
	float len = p_len + b_len;

	//�߂肱��ł��邩
	if (dist <= len) {
	    return true;//�������Ă���
    }
		return false;//�������Ă��Ȃ�

}



void Player::PlayerJump() {

	//�ʒu=�ʒu + ���x * ����
	//���x=���� + �����x * ����
	//��ɃW�����v�A���ɗ�����9.8f�d�ʉ����x
	//G���ɉ���

	//�t���O�ŏ�ԑJ�ڂ��Ǘ�
	static int jumpflag = 0;

	float G = 0.098f;//��1

	static float fcnt = 0;//�t���[���J�E���^

	fcnt+=0.01f;//���Ԃ��o�߂��Ă���

	//Space�L�[�ŃW�����v
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

//�X�V
void Player::PlayerUpdate() {
	
	//-------------------------------------
	// Player Motion
	//-------------------------------------
	//���x�@���W�A���Œ�`�@0.01f
	static float radian = (float)XM_PI / 180;
	XMFLOAT3 vPos;//�ʒu
	XMFLOAT3 vRot;//��]
	//��]�@Y������
	
	if (GetKeyboardPress(DIK_D))
	{
		Yaw += 0.05f;//�� 1��
		//Pos -= Dir * 0.05f;
	}
	if (GetKeyboardPress(DIK_A))
	{
		Yaw -= 0.05f;//�� 1��
	}
	

	static bool b_rot=false;
	//�i�s�����ɐi��
	//z�����̓v���X z>0�A��O�̓}�C�i�Xz<0
	//���j�^�[�X�N���[���̈ʒu�� z=0
	if (GetKeyboardPress(DIK_W))
	{
		Pos -= Dir * 0.05f;//������0.01��������

	}
	if (GetKeyboardPress(DIK_S))
	{
	    Pos += Dir * 0.05f;//������0.01��������
	}
	
	//Dir=XMQuaternionRotationAxis(Dir,Yaw);
	//Dir=XMQuaternionRotationNormal(Dir, Yaw);
	//Dir=XMQuaternionConjugate(Dir);
	//XMVECTOR rot=XMQuaternionRotationRollPitchYawFromVector(Dir);
	//XMStoreFloat3(&vRot, rot);

	


	//�i�s�����ɐi��
	//-------------------------------------
	// Player Motion�X�V
	//-------------------------------------
	
	//XMVECTOR��XMFLOAT3�ɕϊ�
	//float x,float y,float z�����o�����Ƃ��ł���
	XMStoreFloat3(&vPos, Pos);

	//0.0
	if (vPos.y < -0.0f)
	{
		vPos.y = 0.0f;
	}

	//unitychan WorldMatrix����
	//��]Matrix * �ړ�Matrix
	WorldMatrix = XMMatrixRotationY(Yaw) *
		XMMatrixTranslation(vPos.x, vPos.y, vPos.z);
	//unitychan �����x�N�g���ݒ�
	//���[�J�����W���@z������
	
	Dir = WorldMatrix.r[2];//Z��
	
}


//�A�j���[�V����
void Player::PlayerAnimation() {
	
	if (animeTime < animeMaxTime) {
	
		animeTime += 0.01f;

		unitychanRunAnime.SetTransform(animeTime);
	}
	else {

		animeTime = 0.0f;

	}

	
}

//�`��
void Player::PlayerDraw() {

	
	//ImGui::Text("����ƁA�͂�����");
	
	//-------------------------------------
	//�@Unity�����̕\��
	//-------------------------------------

	//�]�u�s��@�萔�o�b�t�@�ɐݒ�
	consBufferMatrix.world = XMMatrixTranspose(
		WorldMatrix);

	

	//GPU�ɒ萔�o�b�t�@�iUnity������World Matrix)��]��
	g_DX11Manager.UpdateConstantBuffer(
		cbuffer.Get(), consBufferMatrix);
	
	//�X�L�����b�V���A�j���[�V���� model �\��
	//����Run Motion

	unitychan.Draw();
	
	
}