#pragma once
#include "UnityExportModel.h"
#include "UnityExportSkinnedModel.h"

#include <DirectXMath.h>

using namespace DirectX;

class Player {
private:

	//Player Transform�@�f�[�^
	XMVECTOR Pos;//�ʒu
	//XMVECTOR Speed;//���x
	FLOAT Speed;
	XMVECTOR Dir; //�����x�N�g��
	FLOAT Yaw;//y�������]�p

	//Player Matrix��`
	XMMATRIX WorldMatrix;//World Matix
	XMMATRIX ScaleMatrix;
	XMMATRIX RotationYMatrix;//��]Matrix
	XMMATRIX TranslationMatrix;//�ړ�Matrix

	//�ړ��t���b�O
	int moveflag;

	//Player Animation ����ϐ��i�R���g���[���[�j
	float animeTime;//= 0.0f;
	float animeMaxTime;// = unichanrun.GetMaxAnimationTime();

public:
	Player() {};
	~Player() {};
	
	//�Q�b�^�[�֐�
	//2021-07-12 ���j��
	XMVECTOR GetPos(){ return Pos; }//�ʒu���擾�p
	void SetPos(XMVECTOR setPos) { Pos = setPos; }//�ʒu�ݒ�p


	//--------------------------------------------
	// OBB Var Area
	//--------------------------------------------
	XMFLOAT3 maxpos = XMFLOAT3(0, 0, 0);
	XMFLOAT3 minpos = XMFLOAT3(0, 0, 0);


	struct OBB {
		XMMATRIX m_WorldMatrix;
		XMVECTOR m_Pos;              // �ʒu
		XMVECTOR m_NormaDirect[3];   // �����x�N�g��
		FLOAT m_fLength[3];          // �e�������̒���
	} obb;

	//�e��֐�
	void PlayerInit();
	void PlayerUninit();

	void PlayerUpdate();

	void PlayerJump();//�W�����v�֐���ǉ�

	void PlayerAnimation();
	
	//2021-.7-12 ���j��
	//���� ���� BoxPos PlayerPos Box���� Player����
	bool PlayerHit(XMFLOAT3 p_pos, XMFLOAT3 b_pos,float p_len,float b_len); //Box�Ƃ̓����蔻�� 
					  //�����������Atrue 
					  //�������ĂȂ����Afalse

	void PlayerDraw();

	
};


class Player* GetPlayer();