#pragma once
#include "Scene.h"
#include "StageBase.h"
#include "ModelManager_Class.h"
#include "Sound.h"

#include "GameClearEvent.h"
#include "GameStartEvent.h"
#include "GameOverEvent.h"
#include "GamePause.h"
#include "GameOver.h"
#include "GameClear.h"

#include "Image2D.h"

#include "KnockUI.h"
#include "BreakNumUI.h"
#include "UI_OverPeople.h"
#include "UI_Tutorial.h"

#include "ObjectRenderer.h"

class Scene_StageBase : public CScene
{
protected:
	enum GAME_STATE
	{
		STATE0_TUTORIAL,	//操作説明表示
		STATE1_STARTEVENT,	//ゲーム開始アニメ
		STATE2_GAME,		//ゲーム画面
		STATE3_PAUSE,		//ポーズ画面
		STATE4_CLEARANIME,	//ゲームクリアアニメ
		STATE5_CLEAR,		//クリア画面
		STATE6_OVERANIME,	//ゲームオーバーアニメ
		STATE7_GAMEOVER,	//ゲームオーバー画面
		STATE8_LASTCLEAR,	//すべてクリアしたときの画面
		STATEMAX,
	};	//ゲーム画面の状態

	enum BACKOBJECT
	{
		AREA_1 = 0,
		AREA_2,
		AREA_3,
		MAX
	};

public:
	Scene_StageBase();
	~Scene_StageBase() override;
	void Update() override;
	void Draw() override;

protected:

	//ステージ初期化関係
	void CreateStage(int Width, int Height, int* BlockMapData,int* JewelyMapData,int* HeetMapData,bool usePilebanker);	//ステージの作成
	void SetState(GAME_STATE nextState);						//次の処理の設定
	void SetBGM(std::string bgmName);							//BGMの設定
	void SetStageScene(SCENE nowScene);							//今のシーンが何番目のステージなのか設定
	void SetBackGround(BACKOBJECT area);						//背景オブジェクトの設定
	void SetTutorialImage(const char* Filepath);				//チュートリアルに使う画像の設定
	void SetLastStage();										//最後のステージの時に呼ぶ関数

	//アップデート関係
	virtual void UpdateTutorial();								//チュートリアル
	virtual void UpdateStartEvent();							//ステージ開始イベント
	virtual void UpdateGame();									//ゲーム
	virtual void UpdatePause();									//ポーズ
	virtual void UpdateClearAnime();							//クリアしたときのイベント
	virtual void UpdateOverAnime();								//オーバーしたときのイベント
	virtual void UpdateClear();									//クリアの選択
	virtual void UpdateOver();									//オーバーの選択
	virtual void UpdateLastStageClear();						//最終ステージのクリアした後のイベント

	//描画関係
	virtual void DrawTutorial();
	virtual void DrawStartEvent();
	virtual void DrawGame();
	virtual void DrawPause();
	virtual void DrawClearAnime();
	virtual void DrawOverAnime();
	virtual void DrawClear();
	virtual void DrawOver();
	virtual void DrawLastStageClear();

private:
	Stage_Base* m_pStage = nullptr;
	GAME_STATE m_gameState;
	SCENE m_NowScene;
	SCENE m_NextScene;
	SaveElea m_SaveSlot;
	bool m_bLastStage = false;

	BGM* m_pBGM = nullptr;

	ObjectRenderer* m_pBackObject = nullptr;

	Game_StartEvent* m_pGameStartEvent = nullptr;
	GameClearEvent* m_pGameClearEvent = nullptr;
	GameOverEvent* m_pGameOverEvent = nullptr;
	GamePause* m_pGamePause = nullptr;
	GameClear* m_pGameClear = nullptr;
	GameOver* m_pGameOver = nullptr;

	//画像
	Image2D* m_pPauseBack = nullptr;
	Image2D* m_pGameBack = nullptr;
	Image2D* m_pInf = nullptr;
	Image2D* m_pAllClearImage = nullptr;	//全クリアしたときの画像が入る
	Image2D* m_pButton = nullptr;			//全クリアしたときのボタン画像
	float m_Alpha = 0.0f;
	UI_OverPeople* m_pPeople = nullptr;
	UI_Tutorial* m_pTutorial = nullptr;

protected:
	SaveData m_SaveData;
};