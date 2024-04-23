//#pragma once
#ifndef GAME_START_EVENT_H
#define GAME_START_EVENT_H

#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "StartEvent_Player.h"
#include "StartEvent_SideBunker.h"

class Game_StartEvent
{
public:
	Game_StartEvent(Stage_Base* pStage);
	~Game_StartEvent();
	void Update();
	void Draw();
	void SetStage(Stage_Base* pStage);
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	bool GetEnd();
	StartEvent_Player* GetPlayer();

private:
	Stage_Base* m_pSceneStage;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	bool m_bEnd;
	StartEvent_Player* m_pPlayer;
	StartEvent_SideBunker* m_pSideBunker;
	FloatSize m_blocksize = { 0.5f, 0.5f, 0.5f };
	float m_blockangle[3] = { 0.0f, 0.0f, 0.0f };
	FloatPos m_BlockDrawPos;
	bool m_BreakBlock = false;
};

#endif // !GAME_START_EVENT_H
