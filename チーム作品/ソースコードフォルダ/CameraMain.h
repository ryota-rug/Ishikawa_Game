#ifndef __CAMERAMAIN_H__
#define __CAMERAMAIN_H__

#include "CameraDebug.h"
#include "XboxKeyboard.h"
#include "StageBase.h"
#include "Player.h"

class CameraMain : public CameraBase
{
public:
	CameraMain(Stage_Base* stage);
	~CameraMain() {};

	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook);
	void MovePlayerCamera();

private:
	void Interpolation();	//�J�������؂�ւ�����Ƃ��̕��	
	DirectX::XMFLOAT3 m_EndPos;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_EndLook;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_StartPos;	//���[���h�J�����̊J�n�n�_
	DirectX::XMFLOAT3 m_StartLook;	//���[���h�J�����̊J�n�n�_
	float m_time;
	float m_totalTime;
	Stage_Base* m_pStage;
	float MinPosX = -300.0f;   //�J�������ړ��ł���X������
	float MaxPosX = 600.0f;    //�J�������ړ��ł���X�����
	float MinPosY = -300.0f;   //�J�������ړ��ł���Y������
	float MaxPosY = 450.0f;    //�J�������ړ��ł���Y�����
	float AddposX = 0.0f;
	float AddposY = 0.0f;
	float AddposZ = 0.0f;
	float OldAddX = 0.0f;
	bool m_b;	//�v���C���[�Ɠ������W�ɂ��邩
	bool m_b2;	//WASD��������Ă���v���C���[�Ɠ������W�ɖ߂�܂�
	bool m_b3;
	float m_time2;
	float m_totalTime2;
	DirectX::XMFLOAT3 a;
	constexpr static float m_posZ = -160.0f;
	constexpr static float m_posY = 60.0f;
	int m_AddMove;
};



#endif // !__CAMERAMAIN_H__

