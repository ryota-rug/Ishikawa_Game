#ifndef __CAMERAPILE_H__
#define __CAMERAPILE_H__

#include "CameraBase.h"
#include "StageBase.h"
#include "PileBankerBase.h"

 void BiblationCameraPile();

class CameraPile :public CameraBase
{
public:
	CameraPile(Stage_Base* Stage);
	~CameraPile() {};
	void Update();
	void ChangeCamera_Init(DirectX::XMFLOAT3 yetPos , DirectX::XMFLOAT3 yetLook) override;
	bool GetPile();
public:
	enum MIGRATE
	{
		CameraInterpolation,
		MIGRATE_SHOT,
		MIGRATE_SIDE,
		MIGRATE_MAX
	};
private:
	void Side();
	void Shot();
	void Shake();
	
	void Interpolation();
private:
	DirectX::XMFLOAT3 m_EndPos;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_EndLook;	//���[���h�J�����̍ŏI�n�_�i��ԉ����������ꏊ�j
	DirectX::XMFLOAT3 m_StartPos;	//���[���h�J�����̊J�n�n�_
	DirectX::XMFLOAT3 m_StartLook;	//���[���h�J�����̊J�n�n�_
	float m_time;
	float m_totalTime;
	DirectX::XMFLOAT3 m_OldPilePos;	//�p�C���̑O�t���[�����W
	DirectX::XMFLOAT3 m_PileMove;	//�p�C���̈ړ���
	
	Stage_Base* m_pStage;
	MIGRATE m_Migrate;
	constexpr static float m_pointZ = -230.0f;
	int m_PileAtk;
	constexpr static int m_ShakeFrame = 10;	//�h���t���[����
	constexpr static int m_ShakeWidth = 10;	//�h��镝�̒��I�i�P�O�Ȃ�-�T�`�T�j
};


#endif // !__CAMERAPILE_H__
