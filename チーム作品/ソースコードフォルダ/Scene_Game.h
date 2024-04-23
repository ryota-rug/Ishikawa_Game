//#pragma once
#ifndef SCENE_PLAY_H
#define SCENE_PLAY_H
#include "Scene.h"
#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Sound.h"

#include "GamePause.h"
#include "GameOver.h"
#include "GameClear.h"

class CScene_Game: public CScene
{
public:
	CScene_Game();
	virtual ~CScene_Game() override;
	virtual void Update() override;
	virtual void Draw() override;

protected:
	enum GAME_STATE
	{
		STATE_GAME,		//ゲーム画面
		STATE_PAUSE,	//ポーズ画面
		STATE_CLEAR,	//クリア画面
		STATE_GAMEOVER	//ゲームオーバー画面
	}m_gameState;	//ゲーム画面の状態

	Stage_Base* m_pStage;
	BGM* m_pBGM;

	GamePause* m_pGamePause;
	GameClear* m_pGameClear;
	GameOver* m_pGameOver;

	bool m_fade;

protected:
	void Fade();
};


#endif // !SCENE_PLAY_H


