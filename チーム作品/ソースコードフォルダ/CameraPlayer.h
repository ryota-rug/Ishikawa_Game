//#pragma once
#ifndef H_CAMERAPLAYER
#define H_CAMERAPLAYER

#include "CameraBase.h"
#include "Player.h"

class CameraPlayer :public CameraBase
{
public :
	CameraPlayer(Player* pPlayer): m_pPlayer(pPlayer),m_rotation(0.0f,0.0f),m_lateX(0.0f),m_lateY(0.0f){}
	~CameraPlayer(){}
	void Update()
	{
		//���_�̐ݒ�
		m_pos.x = 0.0f;
		m_pos.y = 0.0f;
		m_pos.z = -10.0f;

		m_look.x = 0.0f;
		m_look.y = 0.0f;
		m_look.z = 0.0f;
		//�x��āA���Ă����ꍇ�̊p�x���v�Z
		DirectX::XMFLOAT2 Now_Angle;
		m_lateX = (m_rotation.x - m_lateX) * 0.03f + m_lateX;
		m_lateY = (m_rotation.y - m_lateY) * 0.03f + m_lateY;

		//�x�ꂽ�p�x�ŃJ�����̈ʒu�����߂�
		//���ꂽ�p�x�̈ʒu�ɃJ�������ړ�����
		m_pos.y = (sin(Angle_To_Radion(m_lateY)) * 5.0f) + m_look.y;

		//�J�����̃Y�[��
		if (IsKeyPress('U')) { m_fovy -= 0.1f; }		//�A�b�v
		if (IsKeyPress('I')) { m_fovy += 0.1f; }		//�_�E��
	}

	void PlayerN()
	{

	}

private :
	const float RotationSpeed = 1.0f;
	Player *m_pPlayer;
	DirectX::XMFLOAT2 m_rotation;	//�����ׂ��p�x������
	float m_lateX, m_lateY;	//�ړI��ɑ΂��Ēx��Ă��Ă����p�x(���݂̊p�x)
};

#endif //H_CAMEARAPLAYER