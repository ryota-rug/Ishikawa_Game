//#pragma once
#ifndef CAMERADEBUG
#define CAMERADEBUG
#include "Input.h"
#include "CameraBase.h"


void BiblationCameraDebug();

class CameraDebug : public CameraBase
{
public:
	CameraDebug();
	~CameraDebug() {};
	void Update();
private:
	constexpr static int LIMIT_TOP_ANGLE = 30;	//�c�A���O���̏��
	constexpr static int LIMIT_BOTTOM_ANGLE = 150;	//���A���O���̏��
	constexpr static float UD_ANGLE_SPEED = 2.0f;	//�c�A���O���X�s�[�h
	constexpr static float RL_ANGLE_SPEED = 2.0f;	//���A���O���X�s�[�h
	DirectX::XMFLOAT3 f3Flont;		//vFlont�̎󂯔�
	float m_AngleXZ, m_AngleYFlont;	//�x�p
	float m_radXZ, m_radY;	//���W�A���p
	float m_lateXZ, m_lateYFlont;	//�ړI�ʒu�ɑ΂��Ăǂꂾ���x��Ēǂ�����
	
	//���ƂŐ�Ώ����ĂˁI�I�I�I
	DirectX::XMFLOAT3 HINANPOS;
};


#endif //CAMERADEBUG