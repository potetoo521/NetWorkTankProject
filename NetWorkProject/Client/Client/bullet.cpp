#pragma once
#include "character.h"

//�R���X�g���N�^
Bullet::Bullet(float _x, float _y,float _vx,float _vy) {
	img = LoadGraph("image/hitokage.png");

	ID = 3;
	pos.x = _x;//�o���ʒu
	pos.y = _y;

	vec.x = _x;//�����x�N�g��
	vec.y = _y;
}

//����
int Bullet::Action(list<unique_ptr<Base>>& base) {

	////�ړ��x�N�g�������Z
	pos.x += vec.x;
	pos.y += vec.y;

	////��ʂ̒[�ɗ�����A�ړ��x�N�g�����t�ɂ���
	//if (pos.x < 0 || pos.x>736.0f)vec.x = -vec.x;
	//if (pos.y < 0 || pos.y>546.0f)vec.y = -vec.y;

	//if (pos.x < 0 || pos.x>736.0f)ID=-999;
	//if (pos.y < 0 || pos.y>546.0f)ID=-999;
	return 0;
}

//�`��
void Bullet::Draw() {
	DrawGraphF(pos.x, pos.y, img, TRUE);
}





//Object���}�E�X�N���b�N�|�C���g�̈ʒu�Ɉړ�������
//float m_bx    �I�u�W�F�N�g�̍��W X
//float m_by    �I�u�W�F�N�g�̍��W Y
//float* bx     �I�u�W�F�N�g�̃x�N�g�� X
//float* by     �I�u�W�F�N�g�̃x�N�g�� Y
//float speed   �ړ������鑬��
////float flag    �����N���b�N�擾�t���O
//void MousePointBullet(float m_bx, float m_by, float* bx, float* by, float speed, bool* flag)
//{
//	float m_mou_bx;//mouse���ۑ�
//	float m_mou_by;
//	//�}�E�X�̈ʒu���擾
//	if (*flag == true)
//	{
//	//	m_mou_bx = (float)Input::GetPosX();
//	//	m_mou_by = (float)Input::GetPosY();
//
//		//*bx = (m_mou_bx - m_bx) * speed;
//		//*by = (m_by - m_mou_by) * speed;
//
//
//		*flag = false;
//	}
//
//	float r = 0.0f;//������ۑ�
//	r = (*bx) * (*bx) + (*by) * (*by);
//	r = sqrt(r);//r �����[�g�����߂�
//
//	//������0���ǂ������ׂ�
//	if (r == 0.0f)
//	{
//		;//0�Ȃ牽�����Ȃ�
//	}
//	else
//	{
//		//���K�����s��
//		*bx = 1.0f / r * (*bx);
//		*by = 1.0f / r * -(*by);
//	}
//}