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
		STATE_GAME,		//�Q�[�����
		STATE_PAUSE,	//�|�[�Y���
		STATE_CLEAR,	//�N���A���
		STATE_GAMEOVER	//�Q�[���I�[�o�[���
	}m_gameState;	//�Q�[����ʂ̏��

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


