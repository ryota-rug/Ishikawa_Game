#ifndef __CAMERAWORLD_H__
#define __CAMERAWORLD_H__

#include "CameraBase.h"
#include "StageBase.h"

class CameraWorld :public CameraBase
{
public:
	CameraWorld (Stage_Base* Stage);
	~CameraWorld() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook);

private:
	void Interpolation();	//�J�������؂�ւ�����Ƃ��̕��	
	DirectX::XMFLOAT3 m_EndPos;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_EndLook;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_StartPos;	//���[���h�J�����̊J�n�n�_
	DirectX::XMFLOAT3 m_StartLook;	//���[���h�J�����̊J�n�n�_
	float m_time;
	float m_totalTime;

	Stage_Base* m_pStage;
	constexpr static float m_Const = -45.0f;

};


#endif // !__CAMERAWORLD_H__
