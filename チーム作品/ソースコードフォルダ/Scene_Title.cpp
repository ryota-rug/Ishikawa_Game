#include "Scene_Title.h"
#include "WinUtil.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "Game3D.h"
#include "SaveLoad.h"


namespace
{
	int totalUtituke;
	int totalHakai;
	bool roboUp = true;
}



CScene_Title::CScene_Title()
{
	m_pSpriteManager = new SpriteManager;


	//背景
	for (int i = 0; i < 2; i++)
	{
		m_pMoveBack[i] = new Image2D("Assets/2D/Title/title_move.png", m_pSpriteManager);
		m_pMoveBack[i]->pos = { i*1280.0f, 370.0f };
		m_pMoveBack[i]->size = { 1280.0f, 720.0f };
	}
	m_pBack = new Image2D("Assets/2D/Title/title_back.png", m_pSpriteManager);
	m_pBack->pos = { 640.0f, 360.0f };
	m_pBack->size = { 1280.0f, 720.0f };


	//タイトルロゴ
	m_pLogo = new Image2D("Assets/2D/Title/TitleLogo.png", m_pSpriteManager);
	m_pLogo->pos = { 300.0f, 220.0f };
	m_pLogo->size = { 450.0f, 320.0f };

	//矢印
	m_pSelect = new Image2D("Assets/2D/select.png", m_pSpriteManager);
	m_pSelect->pos = { 1200.0f, SELECT_STAGESELECT };
	m_pSelect->size = { 300.0f, 200.0f };


	//文章
	m_pLetterSelect = new Image2D("Assets/2D/Title/ステージセレクト.png", m_pSpriteManager);
	m_pLetterSelect->pos = { 800.0f, SELECT_STAGESELECT };
	m_pLetterSelect->size = { 500.0f, 80.0f };
	m_pLetterOwaru = new Image2D("Assets/2D/Title/オワル.png", m_pSpriteManager);
	m_pLetterOwaru->pos = { 800.0f, SELECT_END };
	m_pLetterOwaru->size = { 500.0f, 80.0f };
	m_pLetterSOUUTITUKE = new Image2D("Assets/2D/Title/ソウウチツケスウ.png", m_pSpriteManager);
	m_pLetterSOUUTITUKE->pos = { 750.0f, 350.0f };
	m_pLetterSOUUTITUKE->size = { 400.0f,60.0f };
	m_pLetterSOUHAKAI = new Image2D("Assets/2D/Title/ソウハカイスウ.png", m_pSpriteManager);
	m_pLetterSOUHAKAI->pos = { 750.0f, 400.0f };
	m_pLetterSOUHAKAI->size = { 400.0f,60.0f };


	//ロボット
	m_pRobo = new Image2D{ "Assets/2D/animation/robot.png", m_pSpriteManager };
	m_pRobo->SetTexScale(4, 1);
	m_pRobo->pos = { -200.0f, 630.0f };
	m_pRobo->size = { 450.0f, 450.0f };

	//数字
	m_pNum = new Image2D{ "Assets/2D/number.png", m_pSpriteManager };
	m_pNum->size = { 50.0f,50.0f };
	m_pNum->SetTexScale(11, 1);


	//BGM
	m_pBGM = new BGM("Assets/BGM/Title.wav", true);
	m_pBGM->SetVolume(0.6f);
	m_pBGM->Start();


	//SE
	m_pSESelect		= new SE("Assets/SE/Destroy_Block.wav"); //選択
	m_pSEDetermine	= new SE("Assets/SE/Tate_Uti.wav");		 //決定


	//入力状態
	m_determine = false;


	//打付数と破壊数を取得
	totalUtituke = 0;
	totalHakai = 0;

	for (int i = 0; i <= 15; i++)
	{
		SaveData data = GetLoadStage((SaveElea)i);
		totalUtituke += data.AllHitnum;
		totalHakai += data.AllBlocknum;
	}

	if (totalUtituke > 9999) { totalUtituke = 9999; }
	if (totalHakai > 9999) { totalHakai = 9999; }
}

CScene_Title::~CScene_Title()
{
	delete m_pSESelect;
	delete m_pSEDetermine;

	m_pBGM->Stop();
	delete m_pBGM;

	delete m_pRobo;
	delete m_pNum;

	for (int i = 0; i < 2; i++) { delete m_pMoveBack[i]; }
	delete m_pBack;

	delete m_pLogo;
	delete m_pSelect;

	delete m_pLetterSelect;
	delete m_pLetterOwaru;
	delete m_pLetterSOUUTITUKE;
	delete m_pLetterSOUHAKAI;

	delete m_pSpriteManager;
}

void CScene_Title::Update()
{
	//------------
	//　自動処理
	//------------
	bool canInput = true; //入力受付フラグ
	DirectX::XMFLOAT2 keypos = GetPressStick();

	//ロボット入場
	if (m_pRobo->pos.x <= 200.0f)
	{
		m_pRobo->pos.x += 15.0f;
		m_pRobo->UpdateAnimation(2, true);
		canInput = false;
	}


	//決定ボタンが押されたら自動処理
	if (m_determine)
	{
		//シーンをロードする
		switch ((int)m_pSelect->pos.y)
		{
		case SELECT_STAGESELECT:
		{
			if (m_pRobo->pos.x <= 1380)
			{
				//ロボットが右に進む
				m_pRobo->pos.x += 20.0f;
				m_pRobo->UpdateAnimation(2, true);
				canInput = false;
			}
			else
			{
				SceneChange(SCENE_SELECT);	//セレクトシーンに移動
				return;
			}
		}
		break;

		case SELECT_END:
		{
			FileSave();
			SceneChange(SCENE_END);	//ゲームを終わる
			return;
		}
		break;
		}
	}


	//ガタガタ
	if (roboUp) //RoboUp
	{
		m_pRobo->pos.y += 0.5f;
		if (m_pRobo->pos.y >= 631.0f) { roboUp = false; }
	}
	else //RoboDown
	{
		m_pRobo->pos.y -= 0.5f;
		if (m_pRobo->pos.y <= 629.0f) { roboUp = true; }
	}


	//背景の移動
	for (int i = 0; i < 2; i++)
	{
		m_pMoveBack[i]->pos.x -= 1.0f;
		if (m_pMoveBack[i]->pos.x == -640) { m_pMoveBack[i]->pos.x = 1920; }
	}


	//選択しているものが変わったら杭が出る
	if (m_pSelect->pos.x > 1200)
	{
		m_pSelect->pos.x -= 10;
		canInput = false;
	}


	if (!canInput) { return; }



	//------------
	//　入力受付
	//------------
	if (IsKeyPress(VK_UP) || InputPressKey(UP_BUTTON) || (InputPressKey(LEFT_STICK) && keypos.y > 0.0f))
	{
		m_pSelect->pos.x = 1400;

		switch ((int)m_pSelect->pos.y)
		{
		case SELECT_STAGESELECT: m_pSelect->pos.y = SELECT_END;			break;
		case SELECT_END:		 m_pSelect->pos.y = SELECT_STAGESELECT;	break;
		}

		//選択音
		m_pSESelect->Play();
	}


	if (IsKeyPress(VK_DOWN) || InputPressKey(DOWN_BUTTON) || (InputPressKey(LEFT_STICK) && keypos.y < 0.0f))
	{
		m_pSelect->pos.x = 1400;

		switch ((int)m_pSelect->pos.y)
		{
		case SELECT_STAGESELECT: m_pSelect->pos.y = SELECT_END;			break;
		case SELECT_END:		 m_pSelect->pos.y = SELECT_STAGESELECT;	break;
		}

		//選択音
		m_pSESelect->Play();
	}


	if (IsKeyPress(VK_RETURN) || InputPressKey(LEFT_TRIGGER) || InputPressKey(A_BUTTON))
	{
		//決定ボタン押したフラグ
		m_determine = true;

		//決定音
		m_pSEDetermine->Play();
	}

	//チート
	if (IsKeyPress('1') && IsKeyPress('5') && IsKeyPress('9'))
	{
		CheatData();
		//決定ボタン押したフラグ
		m_determine = true;

		//決定音
		m_pSEDetermine->Play();
	}
	if (IsKeyPress('2') && IsKeyPress('6') && IsKeyPress('0'))
	{
		ResetData();
		//決定ボタン押したフラグ
		m_determine = true;

		//決定音
		m_pSEDetermine->Play();
	}
}

void CScene_Title::Draw()
{
	EnableDepth(false);

	//背景
	for (int i = 0; i < 2; i++) 
	{
		m_pMoveBack[i]->Draw(); 
	}
	m_pBack->Draw();

	m_pLogo->Draw();
	m_pSelect->Draw();
	m_pRobo->Draw();

	//文字
	m_pLetterOwaru->Draw();
	m_pLetterSelect->Draw();
	m_pLetterSOUUTITUKE->Draw();
	m_pLetterSOUHAKAI->Draw();

	//打付け回数
	m_pNum->pos.y = 350.0f;
	m_pNum->pos.x = 1040.0f;	m_pNum->texNum = totalUtituke / 1000;		m_pNum->Draw();
	m_pNum->pos.x = 1080.0f;	m_pNum->texNum = totalUtituke / 100 % 10;	m_pNum->Draw();
	m_pNum->pos.x = 1120.0f;	m_pNum->texNum = totalUtituke /10 % 10;		m_pNum->Draw();
	m_pNum->pos.x = 1160.0f;	m_pNum->texNum = totalUtituke % 10;			m_pNum->Draw();

	//破壊回数
	m_pNum->pos.y = 400.0f;
	m_pNum->pos.x = 1040.0f;	m_pNum->texNum = totalHakai / 1000;		m_pNum->Draw();
	m_pNum->pos.x = 1080.0f;	m_pNum->texNum = totalHakai / 100 % 10;	m_pNum->Draw();
	m_pNum->pos.x = 1120.0f;	m_pNum->texNum = totalHakai / 10 % 10;	m_pNum->Draw();
	m_pNum->pos.x = 1160.0f;	m_pNum->texNum = totalHakai % 10;		m_pNum->Draw();
}
