//#pragma once
#ifndef PILE_BANKER_H
#define PILE_BANKER_H
#include "Position_struct.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "Sound.h"

class Stage_Base;

class PileBanker
{
public:
	enum PileDirection
	{
		UP = 0,
		RIGHT,
		DOWN,
		LEFT
	};

	enum PileSelect
	{
		PILE_PREPARATION = 0,
		PILE_CHAGE,
		PILE_IN,
		PILE_HITSTOP,
		PILE_INTERPOLATION,
		PILE_ATTACK,
		PILE_STOP,
		PILE_BACK,
		PILE_GAMEOVER,
		PILE_DESTROY,
		MAX
	};

	enum PileDrawTYPE
	{
		PILE_DEFAULT = 0,
		PILE_BIBLATION
	};

public:
	PileBanker(Stage_Base* MyStage);
	virtual ~PileBanker();
	virtual void Update();
	virtual void Draw();
	virtual void UIDraw();
	IntPos GetMap();
	FloatPos GetDraw();
	bool GetHeet();
	int GetAttack();
	float GetSpeed();
	FloatPos GetBasePos();
	PileSelect Get_PileState();
	int Get_Line();
	bool GetDestroy();
	PileDirection GetDirection();
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	void StopBanker();

protected:
	//�X�e�[�^�X-----------------------------
	int m_Attack;
	float m_TempAttack;
	int m_StopCount;
	bool m_Heet;
	const int m_MaxAttack;
	//������---------------------------------
	PileSelect PileState;	//������Ă��铮��
	const float m_Block_BunkerDistance;	//�u���b�N�ƍY�̊Ԃ̒���
	const FloatPos m_BasePosition;	//�Y�̈�ԍ��ň�ԉ��̃|�W�V�����ƂȂ�x�[�X�|�W�V����
	float m_ShotSpeed;	//�Y��łX�s�[�h
	float m_PullSpeed;	//�Y��łX�s�[�h
	float m_CountSpeed;	//�u���b�N�̃T�C�Y�𒴂�����}�b�v��1�ړ����Ă���
	int m_LineNum;		//���ǂ��̃��[����I��ł��邩
	FloatPos m_DrawPos;	//�`�悷��|�W�V����
	IntPos m_MapPos;	//�}�b�v��̃|�W�V����
	Stage_Base* m_pMyStage;	//�X�e�[�W��������
	PileDirection m_Direction;	//�ł��Ă������
	bool m_Destory;	//������
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	bool Collision_Check_EXE;
	FloatPos m_OldPos;
	int m_HitStopCount;
	PileDrawTYPE m_PileDrawState;

	SE* m_pChageSE;
	SE* m_pUtuSE;
	SE* m_pAttackSE;
	SE* m_pStopSE;
};

#endif // !PILE_BANKER_H
