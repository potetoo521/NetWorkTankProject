#pragma once
#include "character.h"

//�R���X�g���N�^
Bullet::Bullet(float _x, float _y, float _vx, float _vy,int _id) {

	img = LoadGraph("image/hitokage.png");//�摜�f�[�^�����[�h

	GetGraphSize(img, &gr_size.x, &gr_size.y);//�摜�T�C�Y���擾

	posd.x = _x;
	posd.y = _y;

	owner_Id = _id;//�쐬��objID
	ID = 1;
	pos.x = _x;//�o���ʒu
	pos.y = _y;

	vec.x = _vx;//�����x�N�g��
	vec.y = _vy;
}

//����
int Bullet::Action(list<unique_ptr<Base>>& base) {

	////�ړ��x�N�g�������Z
	pos.x += vec.x*B_Speed;
	pos.y += vec.y*B_Speed;
	
	////��ʂ̒[�ɗ�����A�ړ��x�N�g�����t�ɂ���
	if (pos.x < 0 || pos.x + gr_size.x>WIDTH) {
		vec.x = -vec.x; 
		++boundNum;//bound���X�V
	}
	if (pos.y < 0 || pos.y + gr_size.y>HEIGHT){ 
		vec.y = -vec.y;
		++boundNum;
	}

	//���˕Ԃ����𒴂���ƍ폜
	if (boundNum > B_Bound)ID = Destroy_ID;

	//�I�u�W�F�N�g�`�F�b�N
	for (auto i = base.begin(); i != base.end(); i++) {

		auto data =((Player*)(*i).get());//Player�f�[�^���L���X�g
		
		if (data->ID != owner_Id && ID != Destroy_ID && data->ID!=ID){  //�쐬���I�u�W�F�N�g�ł͂Ȃ�&�j�󒆂łȂ�

			Pos p_pos{ 0.0f,0.0f }; //�ʒu
			GraphSize p_size{ 0,0 };//�摜�T�C�Y

			p_pos  = data->pos;
			p_size = data->gr_size;
			
			//�����蔻��
			if (CheckHit( pos.x, pos.y, p_pos.x, p_pos.y, gr_size.x, p_size.x )) {
				ID = Destroy_ID;//���X�g����폜
			}
			if (i == base.end())break;

		}
	}

	return 0;
}

//�`��
void Bullet::Draw() {
	//�����蔻��G���A�\��
	DrawCircle(pos.x , pos.y , sqrtf(20), GetColor(0, 255, 0), TRUE);

	DrawLine(posd.x , posd.y , pos.x, pos.y, GetColor(255, 100, 255));//����`��
	//�摜�`��
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