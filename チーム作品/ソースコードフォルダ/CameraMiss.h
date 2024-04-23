#ifndef __CAMERAMISS_H__
#define __CAMERAMISS_H__

#include "CameraBase.h"
#include "StageBase.h"
#include "Player.h"

class CameraMiss : public CameraBase
{
public:
	CameraMiss(Stage_Base* Stage);
	~CameraMiss() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook) override;
	void Set(DirectX::XMFLOAT3 yetPos);
private:
	void Interpolation();	//�J�������؂�ւ�����Ƃ��̕��	

private:
	Stage_Base* m_pStage;
	Stage_Base::GAMEOVER_TYPE m_eType;
	constexpr static float m_pointZ = -200.0f;

	DirectX::XMFLOAT3 m_EndPos;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_EndLook;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_StartPos;	//���[���h�J�����̊J�n�n�_
	DirectX::XMFLOAT3 m_StartLook;	//���[���h�J�����̊J�n�n�_
	float m_time;
	float m_totalTime;

};




#endif // !__CAMERAMISS_H__
