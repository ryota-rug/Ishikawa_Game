#include "Scene_StageBase.h"
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
#include "CameraStartEvent.h"
#include "XboxKeyboard.h"
#include "BillBoard.h"
#include "Area1BackObject.h"
#include "Area2BackObject.h"
#include "Area3BackObject.h"
#include <algorithm>

Scene_StageBase::Scene_StageBase()
{
	m_pStage = nullptr;
	m_pBGM = nullptr;
	m_pBackObject = nullptr;
	m_pGameStartEvent = nullptr;
	m_pGameClearEvent = nullptr;
	m_pGameOverEvent = nullptr;
	m_pGamePause = nullptr;
	m_pGameClear = nullptr;
	m_pGameOver = nullptr;
	m_pPauseBack = nullptr;
	m_pGameBack = nullptr;
	m_pInf = nullptr;
	m_pAllClearImage = nullptr;
	m_pButton = nullptr;
	m_pPeople = nullptr;
	m_pTutorial = nullptr;

	m_bLastStage = false;
}

Scene_StageBase::~Scene_StageBase()
{
	//==============================================
	//画像の削除
	//==============================================
	if (m_pAllClearImage != nullptr) 
		delete m_pAllClearImage;

	if(m_pButton != nullptr) 
		delete m_pButton;

	if (m_pInf != nullptr)	
		delete m_pInf;
	
	if(m_pPauseBack != nullptr)
	delete m_pPauseBack;
	if(m_pBackObject != nullptr)
	delete m_pBackObject;

	if (m_pBGM != nullptr)
	{
		m_pBGM->Stop();
		delete m_pBGM;
	}

	if(m_pTutorial != nullptr)
	delete m_pTutorial;
	if(m_pGameBack != nullptr)
	delete m_pGameBack;
	if(m_pPeople)
	delete m_pPeople;

	if(m_pSpriteManager != nullptr)
	delete m_pSpriteManager;
	if(m_ModelManager != nullptr)
	delete m_ModelManager;
	if(m_pCameraManager != nullptr)
	delete m_pCameraManager;

	if(m_pGameOver != nullptr)
	delete m_pGameOver;
	if(m_pGameClear != nullptr)
	delete m_pGameClear;

	if(m_pGamePause != nullptr)
	delete m_pGamePause;
	if(m_pGameOverEvent != nullptr)
	delete m_pGameOverEvent;
	if(m_pGameClearEvent != nullptr)
	delete m_pGameClearEvent;
	if(m_pGameStartEvent != nullptr)
	delete m_pGameStartEvent;

	if (m_pStage != nullptr)
		delete m_pStage;
}

void Scene_StageBase::Update()
{
	m_pCameraManager->Update();

	//各ステータスに合ったアップデートを行う
	switch (m_gameState)
	{
	case Scene_StageBase::STATE0_TUTORIAL:
		UpdateTutorial();
		break;
	case Scene_StageBase::STATE1_STARTEVENT:
		UpdateStartEvent();
		break;
	case Scene_StageBase::STATE2_GAME:
		UpdateGame();
		break;
	case Scene_StageBase::STATE3_PAUSE:
		UpdatePause();
		break;
	case Scene_StageBase::STATE4_CLEARANIME:
		UpdateClearAnime();
		break;
	case Scene_StageBase::STATE5_CLEAR:
		UpdateClear();
		break;
	case Scene_StageBase::STATE6_OVERANIME:
		UpdateOverAnime();
		break;
	case Scene_StageBase::STATE7_GAMEOVER:
		UpdateOver();
		break;
	case Scene_StageBase::STATE8_LASTCLEAR:
		UpdateLastStageClear();
		break;
	}
}

void Scene_StageBase::Draw()
{
	//各ステータスに合った描画を行う
	switch (m_gameState)
	{
	case Scene_StageBase::STATE0_TUTORIAL:
		DrawTutorial();
		break;
	case Scene_StageBase::STATE1_STARTEVENT:
		DrawStartEvent();
		break;
	case Scene_StageBase::STATE2_GAME:
		DrawGame();
		break;
	case Scene_StageBase::STATE3_PAUSE:
		DrawPause();
		break;
	case Scene_StageBase::STATE4_CLEARANIME:
		DrawClearAnime();
		break;
	case Scene_StageBase::STATE5_CLEAR:
		DrawClear();
		break;
	case Scene_StageBase::STATE6_OVERANIME:
		DrawOverAnime();
		break;
	case Scene_StageBase::STATE7_GAMEOVER:
		DrawOver();
		break;
	case Scene_StageBase::STATE8_LASTCLEAR:
		DrawLastStageClear();
		break;
	}
}

void Scene_StageBase::CreateStage(int Width, int Height, int* BlockMapData, int* JewelyMapData, int* HeetMapData,bool UsePilebankder)
{
	m_pStage = new Stage_Base();					//ステージ(プレイヤー、ブロック、パイルバンカーの情報)の生成
	m_pStage->CreateStage(Width, Height, BlockMapData,JewelyMapData,HeetMapData);	//作ってほしいステージの情報を渡す
	m_pStage->CreatePlayer();														//プレイヤーの生成
	if (!UsePilebankder)															//横に打つパイルバンカーを使わない場合
	{
		m_pStage->SetCantTypeIn_Side();
	}

	//各ゲームステートの初期化
	m_pGameStartEvent = new Game_StartEvent(m_pStage);	//入場アニメーションの初期化
	m_pGameClearEvent = new GameClearEvent(m_pStage);	//クリアアニメーションの初期化
	m_pGameOverEvent = new GameOverEvent(m_pStage);		//オーバーアニメーションの初期化
	m_pGamePause = new GamePause;						//ポーズ画面の初期化
	m_pGameClear = new GameClear(m_pStage);				//クリア画面の初期化
	m_pGameOver = new GameOver(m_pStage);				//オーバー画面の初期化

	//カメラマネージャーとモデルマネージャーの生成
	m_pCameraManager = new C_Camera_Game(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_ADMISSION, m_pStage);		//最初のカメラの設定と各カメラにステージの情報を渡してやる
	Camera_StartEvent* pCameraStartEvent = new Camera_StartEvent(m_pGameStartEvent);								//スタートアニメ用カメラの設定
	m_pCameraManager->AddCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_STARTEVENT, pCameraStartEvent);	//スターとアニメカメラの追加
	m_pCameraManager->ChangeTypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_STARTEVENT);				//最初に使うカメラの設定
	m_ModelManager = new CModelManager(m_pCameraManager->Get_SceneCamera());										//カメラ情報の取得

	//カメラマネージャーとモデルマネージャーを設定
	m_pStage->SetModelManager(m_ModelManager);
	m_pStage->SetCameraManager(m_pCameraManager);
	m_pGameStartEvent->SetModelManager(m_ModelManager);
	m_pGameStartEvent->SetCameraManager(m_pCameraManager);
	m_pGameClearEvent->SetModelManager(m_ModelManager);
	m_pGameClearEvent->SetCameraManager(m_pCameraManager);
	m_pGameOverEvent->SetModelManager(m_ModelManager);
	m_pGameOverEvent->SetCameraManager(m_pCameraManager);

	// 地上に人を表示
	m_pSpriteManager = new SpriteManager;
	BillBoard::_SetCamera(m_pCameraManager->Get_SceneCamera());
	m_pPeople = new UI_OverPeople(m_pSpriteManager);

	//ゲーム背景
	m_pGameBack = new Image2D("Assets/2D/sky.png", m_pSpriteManager);
	m_pGameBack->size = { 1280.0f,720.0f };

	m_pTutorial = new UI_Tutorial;
}

void Scene_StageBase::SetState(GAME_STATE nextState)
{
	m_gameState = nextState;
}

void Scene_StageBase::SetBGM(std::string bgmName)
{
	m_pBGM = new BGM(bgmName.c_str(), true);
	m_pBGM->SetVolume(0.6f);
	m_pBGM->Start();
}

void Scene_StageBase::SetStageScene(SCENE nowScene)
{
	m_NowScene = nowScene;
	m_NextScene = (SCENE)(nowScene + 1);
	m_SaveSlot = static_cast<SaveElea>(static_cast<int>(m_NowScene) - static_cast<int>(SCENE::SCENE_STAGE1_1));
	//セーブデータを入れてやる
	m_SaveData = GetLoadStage(m_SaveSlot);
}

void Scene_StageBase::SetBackGround(BACKOBJECT area)
{
	//背景オブジェクトの生成
	switch (area)
	{
	case Scene_StageBase::AREA_1:
		m_pBackObject = new Area1BackObject(m_ModelManager);
		//セレクト画面背景
		m_pPauseBack = new Image2D("Assets/2D/select/Stage1_Back.png", m_pSpriteManager);
		break;
	case Scene_StageBase::AREA_2:
		m_pBackObject = new Area2BackObject(m_ModelManager);
		//セレクト画面背景
		m_pPauseBack = new Image2D("Assets/2D/select/Stage2_Back.png", m_pSpriteManager);
		break;
	case Scene_StageBase::AREA_3:
		m_pBackObject = new Area3BackObject(m_ModelManager);
		//セレクト画面背景
		m_pPauseBack = new Image2D("Assets/2D/select/Stage3_Back.png", m_pSpriteManager);
		break;
	}
	m_pPauseBack->pos = { 640, 360 };
	m_pPauseBack->size = { 1280, 720 };
	m_pBackObject->SetStage(m_pStage);
}

void Scene_StageBase::SetTutorialImage(const char* Filepath)
{
	//操作説明画像
	m_pInf = new Image2D(Filepath, m_pSpriteManager);
	m_pInf->pos = { 640, 360 };
	m_pInf->size = { 1280 * 0.8f, 720 * 0.8f };
}

void Scene_StageBase::SetLastStage()
{
	m_bLastStage = true;
	//AllClear画像の初期化
	m_pAllClearImage = new Image2D("Assets/2D/Clear/clear.png", m_pSpriteManager);
	m_pAllClearImage->pos = { 640.0f, 360.0f };
	m_pAllClearImage->size = { 1280.0f, 720.0f };
	m_Alpha = 0.0f;

	//Pushボタン初期化
	m_pButton = new Image2D("Assets/2D/Clear/push.png", m_pSpriteManager);
	m_pButton->pos = { 800.0f, 660.0f };
	float ImageRatio = 0.07f;
	m_pButton->size = { 6721.0f * ImageRatio, 1059.0f * ImageRatio };
}

void Scene_StageBase::UpdateTutorial()
{
	m_pTutorial->Update();

	if (IsKeyTrigger(VK_TAB) || InputTriggerKey(LEFT_TRIGGER) || AllKeyTrigger())
	{
		SetAgain(m_SaveSlot, true);
		m_gameState = GAME_STATE::STATE1_STARTEVENT;
	}
}

void Scene_StageBase::UpdateStartEvent()
{
	m_pGameStartEvent->Update();

	//処理が終わればゲームに変更
	if (m_pGameStartEvent->GetEnd())
	{
		m_gameState = GAME_STATE::STATE2_GAME;
	}

	if (IsKeyTrigger(VK_RETURN) || InputTriggerKey(LEFT_TRIGGER) || AllKeyTrigger())
	{
		m_gameState = GAME_STATE::STATE2_GAME;
	}
}

void Scene_StageBase::UpdateGame()
{
	m_pStage->Update();
	m_pStage->PlayerUpdate();
	m_pStage->BlockUpdate();
	m_pStage->NvigateUpdate();
	m_pStage->JewelyUpdate();
	m_pStage->HeetUpdate();

	if (IsKeyTrigger(VK_ESCAPE) || InputTriggerKey(BACK_BUTTON) || InputTriggerKey(B_BUTTON))
	{
		m_gameState = GAME_STATE::STATE3_PAUSE;
		m_pGamePause->PauseInit();
		m_pBGM->SetVolume(0.1f);
	}

	if (m_pStage->Get_GameClear())
	{
		m_gameState = GAME_STATE::STATE4_CLEARANIME;
		m_pGameClearEvent->ClearEventInit();
	}

	if (m_pStage->Get_GameOver())
	{
		m_gameState = GAME_STATE::STATE6_OVERANIME;
		m_pGameOverEvent->OverEventInit();
	}
}

void Scene_StageBase::UpdatePause()
{
	if (m_pGamePause->Update())
	{
		switch (m_pGamePause->GetEXE())
		{
		case GamePause::PauseSelect::RETRY:
			SceneChange(m_NowScene);
			break;
		case GamePause::PauseSelect::STAGESELECT:
			SceneChange(SCENE_SELECT);
			break;
		case GamePause::PauseSelect::SELECTEND:
			SceneChange(SCENE_END);
			break;
		case GamePause::PauseSelect::SELECTGAMERETURN:
			m_gameState = GAME_STATE::STATE2_GAME;
			m_pBGM->SetVolume(0.6f);
			break;
		}
	}
}

void Scene_StageBase::UpdateClearAnime()
{
	m_pStage->BlockUpdate();

	m_pGameClearEvent->Update();

	//ゲームクリアのイベントが終わったら
	if (m_pGameClearEvent->GetEnd())
	{
		SetSave(m_SaveSlot, true, true, m_pStage->GetPlayer()->GetKnock()->GetKnockCnt(), m_pStage->GetBreakInfo()->GetBreckCnt());
		m_pBGM->SetVolume(0.1f);

		if (m_bLastStage)	//今やっているステージが最後のステージだった場合
		{
			//一度クリアしていたら、そのままフェードアウト
			if (m_SaveData.ClearStage)
			{
				SceneChange(SCENE_SELECT);
				return;
			}

			m_gameState = GAME_STATE::STATE8_LASTCLEAR;
		}
		else
		{
			m_gameState = GAME_STATE::STATE5_CLEAR;
			m_pGameClear->ClearInit();
		}
	}
}

void Scene_StageBase::UpdateOverAnime()
{
	m_pGameOverEvent->Update();

	//ゲームクリアのイベントが終わったら
	if (m_pGameOverEvent->GetEnd())
	{
		m_gameState = STATE7_GAMEOVER;
		m_pGameOver->OverInit();
		m_pBGM->SetVolume(0.1f);
	}
}

void Scene_StageBase::UpdateClear()
{
	if (m_pGameClear->Update())
	{
		switch (m_pGameClear->GetEXE())
		{
		case GameClear::ClearSelect::SELECT_RETRY:
			SceneChange(m_NowScene);
			break;
		case GameClear::ClearSelect::SELECT_NEXT:
			SceneChange(m_NextScene);
			break;
		case GameClear::ClearSelect::SELECT_STAGESELECT:
			SceneChange(SCENE_SELECT);
			break;
		}
	}
}

void Scene_StageBase::UpdateOver()
{
	if (m_pGameOver->Update())
	{
		switch (m_pGameOver->GetEXE())
		{
		case GameOver::OverSelect::RETRY:
			SceneChange(m_NowScene);
			break;
		case GameOver::OverSelect::STAGESELECT:
			SceneChange(SCENE_SELECT);
			break;
		}
	}
}

void Scene_StageBase::UpdateLastStageClear()
{
	m_pStage->BlockUpdate();

	m_pGameClearEvent->Update();

	if (m_Alpha >= 1.0f)
	{
		if (IsKeyAnyTrigger() || AllKeyTrigger() > 0)
		{
			SceneChange(SCENE_SELECT);
		}
	}
}

void Scene_StageBase::DrawTutorial()
{
	EnableDepth(false);
	m_pGameBack->Draw();
	EnableDepth(true);
	m_pStage->BlockDraw();
	//ステージの背景オブジェクト描画
	m_pBackObject->Draw();
	EnableDepth(false);
	m_pInf->Draw();
	m_pTutorial->Draw();
	EnableDepth(true);
}

void Scene_StageBase::DrawStartEvent()
{
	EnableDepth(false);
	m_pGameBack->Draw();
	EnableDepth(true);
	m_pGameStartEvent->Draw();
	m_pStage->BlockDraw();
	m_pStage->ItemDraw();
	m_pStage->NvigateDraw();
	m_pBackObject->Draw();
	Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
}

void Scene_StageBase::DrawGame()
{
	EnableDepth(false);
	m_pGameBack->Draw();
	EnableDepth(true);
	m_pStage->Draw();
	m_pStage->StageDraw();
	m_pBackObject->Draw();
	m_pPeople->Draw();
	Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
	m_pStage->UIDraw();
}

void Scene_StageBase::DrawPause()
{
	m_pPauseBack->Draw();
	m_pStage->Draw();
	m_pStage->StageDraw();
	m_pBackObject->Draw();
	Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
	m_pGamePause->Draw();
}

void Scene_StageBase::DrawClearAnime()
{
	EnableDepth(false);
	m_pGameBack->Draw();
	EnableDepth(true);
	m_pStage->Draw();
	m_pStage->PlayerDraw();
	m_pStage->ItemDraw();
	m_pStage->BlockDraw();

	m_pBackObject->Draw();
	m_pPeople->Draw();
	Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
	m_pGameClearEvent->Draw();
}

void Scene_StageBase::DrawOverAnime()
{
	EnableDepth(false);
	m_pGameBack->Draw();
	EnableDepth(true);
	m_pStage->Draw();
	m_pStage->PlayerDraw();
	m_pStage->ItemDraw();
	m_pStage->BlockDraw();
	m_pBackObject->Draw();
	m_pPeople->Draw();
	Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
	m_pGameOverEvent->Draw();
}

void Scene_StageBase::DrawClear()
{
	m_pGameClear->Draw();
}

void Scene_StageBase::DrawOver()
{
	m_pGameOver->Draw();
}

void Scene_StageBase::DrawLastStageClear()
{
	EnableDepth(false);
	m_pPauseBack->Draw();
	EnableDepth(true);
	m_pStage->Draw();
	m_pStage->PlayerDraw();
	m_pStage->ItemDraw();
	m_pStage->BlockDraw();
	m_pBackObject->Draw();
	m_pPeople->Draw();
	Effect_Manager::Draw_Effect(m_pCameraManager->Get_NowCamera());
	m_pGameClearEvent->Draw();		

	//始めてクリアした場合
	if (!m_SaveData.ClearStage)
	{
		m_Alpha += 0.1f;
		m_Alpha = m_Alpha >= 1.0f ? 1.0f : m_Alpha;
		m_pAllClearImage->color = { 1.0f,1.0f,1.0f,m_Alpha };
		m_pAllClearImage->Draw();
	}

	EnableDepth(false);
	m_pButton->Draw();
}