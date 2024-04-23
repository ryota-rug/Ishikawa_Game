//#pragma once
#ifndef GAME_END_EVENT_H
#define GAME_END_EVENT_H

#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Camera_Manager.h"
#include "StartEvent_Player.h"
#include "Sound.h"
#include "SpriteManager.h"
#include "UI_OverPeople.h"

class GameOverEvent
{
public:
	GameOverEvent(Stage_Base* pStage);
	~GameOverEvent();
	void Update();
	void Draw();
	void SetStage(Stage_Base* pStage);
	void SetModelManager(CModelManager* pModelManager);
	void SetCameraManager(C_CameraManager* pCameraManager);
	bool GetEnd();
	void OverEventInit();

private:
	Stage_Base* m_pSceneStage;
	CModelManager* m_pModelManager;
	C_CameraManager* m_pCameraManager;
	bool m_bEnd;
	int m_Count;
	Stage_Base::GAMEOVER_TYPE m_GameOverType;
	DirectX::XMFLOAT3 PlayerPos;
	int m_EffectFrame = 0;
	int m_AnimFrame = 0;
	Effekseer::Handle m_HimeiHandle;

	SpriteManager* m_pSpriteManager;
	UI_OverPeople* m_pImage_Peopre;

	SE* m_pHimei;
};

#endif // !GAME_END_EVENT_H