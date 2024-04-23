//#pragma once
#ifndef __STARTEVENT_SIDEBUNKER_H__
#define __STARTEVENT_SIDEBUNKER_H__
#include "ModelManager_Class.h"
#include "StartEvent_Player.h"
#include "Sound.h"

class StartEvent_SideBunker
{
public:
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
		PILE_DESTROY,
		MAX
	};

	StartEvent_SideBunker(Stage_Base* MyStage, StartEvent_Player* pPlayer);
	~StartEvent_SideBunker();
	void Update();
	void Draw();
	bool GetDestroy() { return m_Destory; }
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
private:
	StartEvent_Player* m_pPlayer;
	int m_AddMap;
	const int m_Range;
	FloatPos m_InstancePos;
	float m_SideSize;
	PileSelect PileState;
	SE* m_pUtuSE;
	SE* m_pAttackSE;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	int m_StopCount;
	float m_Block_BunkerDistance;	//�u���b�N�ƍY�̊Ԃ̒���
	FloatPos m_BasePosition;	//�Y�̈�ԍ��ň�ԉ��̃|�W�V�����ƂȂ�x�[�X�|�W�V����
	float m_Speed;	//�Y��łX�s�[�h
	FloatPos m_DrawPos;	//�`�悷��|�W�V����
	FloatPos m_BlockPos;
	bool m_Destory;	//������
	bool Collision_Check_EXE;
};

#endif //__STARTEVENT_SIDEBUNKER_H__