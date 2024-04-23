#include "Scene_Game.h"
#include "Timer.h"
#include "Game3D.h"
#include "Geometory.h"
#include "CameraDebug.h"
#include "DebugConsole.h"
#include "PileBankerBase.h"
#include "StageBase.h"
#include "Camera_Manager.h"
#include "CameraManager_Game.h"
#include "Input.h"
#include "Effect_Manager.h"

#include <mutex>


CScene_Game::CScene_Game()
{
	m_pStage = new Stage_Base();
	const int X = 7, Y = 8;
	int BlockInfo[X * Y] =
	{
		 4, 4, 4, 4, 4, 4, 4,
		 2, 5, 2, 2, 2, 2, 2,
		 2, 5, 2, 2,10, 2, 8,
		 2, 5, 2, 2,10, 3, 2,
		 8, 2, 2, 2, 2, 3, 2,
		 2, 3, 2, 2, 2, 3, 2,
		 2, 3, 2, 2, 2, 3, 2,
		 2, 3, 2, 2, 2, 3, 2,
	};

	int JewelyInfo[X * Y] =
	{
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,1,0,
		0,0,0,0,0,0,0,
		0,1,0,0,0.0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0

	};

	int HeetInfo[X * Y] =
	{
		0,0,0,0,0,0,0,
		2,0,0,0,0,0,0,
		2,0,2,0,0,0,0,
		2,0,2,0,0,0,0,
		0,0,2,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0,
		0,0,0,0,0,0,0
	};

	m_pStage->CreateStage(X, Y, BlockInfo, JewelyInfo, HeetInfo);
	///m_pStage->CreateStage(5, 5, "a");
	m_pStage->CreatePlayer();

	m_pCameraManager = new C_Camera_Game(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_DEBUG, m_pStage);	//カメラのまとまった情報を作る
	m_ModelManager = new CModelManager(m_pCameraManager->Get_SceneCamera());

	m_pStage->SetModelManager(m_ModelManager);
	m_pStage->SetCameraManager(m_pCameraManager);

	m_pSpriteManager = new SpriteManager;

	//モデルの作成
	m_ModelManager->c_AddModel("Stage", "Assets/Stage/NewStage/TestStage.fbx");
	
	//ゲーム中に切り替える画面の初期化
	m_pGamePause = new GamePause;
	m_pGameClear = new GameClear(m_pStage);
	m_pGameOver = new GameOver(m_pStage);

	//BGMの初期化・音量設定・再生
	m_pBGM = new BGM("Assets/BGM/Stage1.wav", true);
	m_pBGM->SetVolume(0.2f);
	m_pBGM->Start();

	//ゲーム状態の設定
	m_gameState = STATE_GAME;
	m_fade = false;
}


CScene_Game::~CScene_Game()
{
	m_pBGM->Stop();
	delete m_pBGM;

	delete m_pGamePause;
	delete m_pGameClear;
	delete m_pGameOver;

	delete m_pSpriteManager;
	delete m_ModelManager;
	delete m_pCameraManager;

	if (m_pStage)
	{
		delete m_pStage;
	}
}


void CScene_Game::Update()
{
	switch (m_gameState)
	{
	case CScene_Game::STATE_GAME:

		m_pStage->Update();
		m_pStage->PlayerUpdate();
		m_pStage->BlockUpdate();
		m_pStage->NvigateUpdate();
		m_pStage->JewelyUpdate();
		m_pStage->HeetUpdate();
		m_pCameraManager->Update();

		if (IsKeyTrigger(VK_CONTROL))
		{
			m_gameState = STATE_PAUSE;
			m_pGamePause->PauseInit();
			m_pBGM->SetVolume(0.1f);
		}

		if (m_pStage->Get_GameClear())
		{
			m_gameState = STATE_CLEAR;
			m_pGameClear->ClearInit();
			m_pBGM->SetVolume(0.1f);
		}

		if (m_pStage->Get_GameOver())
		{
			m_gameState = STATE_GAMEOVER;
			m_pGameOver->OverInit();
			m_pBGM->SetVolume(0.1f);
		}

		break;


	case CScene_Game::STATE_PAUSE:

		if (m_pGamePause->Update())
		{
			switch (m_pGamePause->GetEXE())
			{
			case GamePause::PauseSelect::RETRY:
				SceneChange(SCENE_GAME);
				break;
			case GamePause::PauseSelect::STAGESELECT:
				SceneChange(SCENE_SELECT);
				break;
			case GamePause::PauseSelect::SELECTEND:
				SceneChange(SCENE_END);
				break;
			case GamePause::PauseSelect::SELECTMAX:
				
				break;
			default:
				break;
			}
		}

		if (IsKeyTrigger(VK_CONTROL)) 
		{
			m_gameState = STATE_GAME;
			m_pBGM->SetVolume(0.2f);
		}

		break;


	case CScene_Game::STATE_CLEAR:

		if (!m_fade)
		{
			Fade();
			m_fade = true;
		}

		if (m_pGameClear->Update())
		{
			switch (m_pGameClear->GetEXE())
			{
			case GameClear::ClearSelect::SELECT_RETRY:
				SceneChange(SCENE_GAME);
				break;
			case GameClear::ClearSelect::SELECT_NEXT:
				SceneChange(SCENE_STAGE1_1);
				break;
			case GameClear::ClearSelect::SELECT_STAGESELECT:
				SceneChange(SCENE_SELECT);
				break;
			case GameClear::ClearSelect::SELECT_MAX:
				break;
			default:
				break;
			}
		}

		if (IsKeyTrigger(VK_CONTROL))
		{
			m_gameState = STATE_GAME;
			m_pBGM->SetVolume(0.2f);
		}

		break;


	case CScene_Game::STATE_GAMEOVER:

		if (!m_fade)
		{
			Fade();
			m_fade = true;
		}

		if (m_pGameOver->Update())
		{
			switch (m_pGameOver->GetEXE())
			{
			case GameOver::OverSelect::RETRY:
				SceneChange(SCENE_GAME);
				break;
			case GameOver::OverSelect::STAGESELECT:
				SceneChange(SCENE_SELECT);
				break;
			case GameOver::OverSelect::SELECTMAX:
				break;
			default:
				break;
			}
		}

		if (IsKeyTrigger(VK_CONTROL))
		{
			m_gameState = STATE_GAME;
			m_pBGM->SetVolume(0.2f);
		}

		break;
	}
}


void CScene_Game::Draw()
{
	switch (m_gameState)
	{
	case CScene_Game::STATE_GAME:
		m_pStage->Draw();
		m_pStage->StageDraw();
		m_ModelManager->c_ModelDraw("Stage", 0.0f, -248.6f,0.0f, 10.6f, 10.6f, 10.6f, 0.0f, 180.0f, 0.0f);
		Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
		m_pStage->UIDraw();
		break;

	case CScene_Game::STATE_PAUSE:
		m_pStage->Draw();
		m_pStage->StageDraw();
		m_ModelManager->c_ModelDraw("Stage", 0.0f, -248.6f, 0.0f, 10.6f, 10.6f, 10.6f, 0.0f, 180.0f, 0.0f);
		Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
		m_pGamePause->Draw();
		break;

	case CScene_Game::STATE_CLEAR:
		m_pGameClear->Draw();
		break;

	case CScene_Game::STATE_GAMEOVER:
		m_pGameOver->Draw();
		break;
	}
}


void CScene_Game::Fade()
{
	InitTimer((Frame)60);
	Image2D* pImage = new Image2D("Assets/2D/Black.png", m_pSpriteManager);


	//フェードアウト
	while (true)
	{
		if (UpdateTimer())
		{
			Draw();
			pImage->Draw();
		}

		if (true) { break; }
	}


	//フェードイン
	while (true)
	{
		if (UpdateTimer())
		{
			Draw();
			pImage->Draw();
		}

		if (true) { break; }
	}


	delete pImage;
	UninitTimer();
}
