#ifndef __CAMERACLEAR_H__
#define __CAMERACLEAR_H__

#include "CameraBase.h"
#include "StageBase.h"
#include "Player.h"

class CameraClear : public CameraBase
{
public:
	CameraClear(Stage_Base* Stage);
	~CameraClear() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook) override;

private:
	void Interpolation();	//�J�������؂�ւ�����Ƃ��̕��	
	
	Stage_Base* m_pStage;
	constexpr static float m_pointY = 30.0f;
	constexpr static float m_pointZ = -80.0f;

	DirectX::XMFLOAT3 m_EndPos;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_EndLook;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_StartPos;	//���[���h�J�����̊J�n�n�_
	DirectX::XMFLOAT3 m_StartLook;	//���[���h�J�����̊J�n�n�_
	float m_time;
	float m_totalTime;
};


#endif // !__CAMERACLEAR_H__
