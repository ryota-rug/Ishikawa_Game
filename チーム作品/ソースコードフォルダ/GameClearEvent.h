//#pragma once
#ifndef GAME_CLEAR_EVENT_H
#define GAME_CLEAR_EVENT_H

#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "StartEvent_Player.h"
#include "ClearEffect.h"
#include "SpriteManager.h"
#include "Effect_Manager.h"

class GameClearEvent
{
public:
	GameClearEvent(Stage_Base* pStage);
	~GameClearEvent();
	void Update();
	void Draw();
	void ClearEventInit();
	void SetStage(Stage_Base* pStage);
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	bool GetEnd();

private:
	Stage_Base* m_pSceneStage;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	SpriteManager* m_pSpriteManager;
	ClearEffect* m_pEffect;
	bool m_bEnd;
	int m_Count;
	Effekseer::Handle m_ClearHandle;
};


#endif // !GAME_CLEAR_EVENT_H

