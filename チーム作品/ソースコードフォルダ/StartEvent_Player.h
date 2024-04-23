//#pragma once
#ifndef STARTEVENT_PLAYER
#define STARTEVENT_PLAYER
#include "Position_struct.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "StageBase.h"
#include "Sound.h"

class StartEvent_Player
{
public:
	enum Event_PlayerState
	{
		MOVE = 0,
		END,
		MAX,
		CHARGE,
		KNOCK
	};

public:
	StartEvent_Player(Stage_Base* pStage);
	~StartEvent_Player();
	void Update();
	void Draw();
	void SetStage(Stage_Base* pStage);
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	Event_PlayerState GetPlayerState();
	FloatPos GetPos();
	FloatPos GetStageEdge() { return StageEdge; }
	bool GetAnimFlg(){ return m_AnimFlg; }
	void SetBreakBlockFlg() { m_BreakBlock = true; }
	bool GetBreakBlockFlg() { return m_BreakBlock; }
	void SetState(Event_PlayerState state) { m_NowPlayerState = state; }
private:
	FloatPos m_pos;
	FloatPos StageEdge;
	FloatPos m_Rotation;
	Stage_Base* m_pSceneStage;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	FloatPos m_StagePlayerPos;
	Event_PlayerState m_NowPlayerState;
	bool m_BreakBlock = false;// ブロックを壊したか
	bool m_AnimFlg;// アニメーション変更したか
	int m_Animframe = 0;
	int m_SEframe = 0;
	SE* m_pWalkSE;
	SE* m_pUtuSE;
};

#endif // !STARTEVENT_PLAYER

