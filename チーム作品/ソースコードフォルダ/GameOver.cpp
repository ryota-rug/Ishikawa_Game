#include "GameOver.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "DirectX.h"
#include "StageBase.h"

GameOver::GameOver(Stage_Base* pStage)
	:m_pBackGround(nullptr),
	m_NowState(OverState::INIT),
	m_NowSelect(OverSelect::RETRY),
	m_NowEXE(false),
	m_pStage(pStage)
{
	m_pSpriteManager = new SpriteManager();

	m_pBackGround = new Image2D{ "Assets/2D/Black.png",m_pSpriteManager };
	m_pBackGround->pos = { 640.0f, 360.0f };
	m_pBackGround->size = { 1280.0f, 720.0f };
	m_pBackGround->angle = { 0.0f, 0.0f, 0.0f };
	m_pBackGround->color = { 1.0f,1.0f,1.0f,0.6f };

	m_pImage_Screen = new UI_OverScreen();

	m_pGameOverInfo = nullptr;
}

GameOver::~GameOver()
{
	if (m_pGameOverInfo != nullptr)
	{
		delete m_pGameOverInfo;
	}

	delete m_pBackGround;

	delete m_pImage_Screen;

	delete m_pSpriteManager;
}

bool GameOver::Update()
{
	m_NowEXE = false;

	m_pImage_Screen->Update();

	DirectX::XMFLOAT2 keypos = GetPressStick();

	switch (m_NowState)
	{
	case OverState::INIT:
		m_NowSelect = OverSelect::RETRY;
		m_NowState = OverState::SELECT;
		m_pImage_Screen->ScreenInit();
		break;
	case OverState::SELECT:
		//下ボタンを押す
		if (IsKeyTrigger(VK_DOWN) || InputTriggerKey(DOWN_BUTTON)
			|| (InputPressKey(LEFT_TRIGGER) && keypos.y < 0.0f))
		{
			int SelectNum = m_NowSelect;
			int MaxNum = OverSelect::SELECTMAX;
			SelectNum = (SelectNum + 1) % MaxNum;

			m_NowSelect = (OverSelect)SelectNum;
		}

		//上ボタンを押す
		if (IsKeyTrigger(VK_UP) || InputTriggerKey(UP_BUTTON)
			|| (InputPressKey(LEFT_TRIGGER) && keypos.y > 0.0f))
		{
			int SelectNum = m_NowSelect;
			int MaxNum = OverSelect::SELECTMAX;
			SelectNum = (SelectNum - 1 + MaxNum) % MaxNum;

			m_NowSelect = (OverSelect)SelectNum;
		}

		if (IsKeyTrigger(VK_RETURN) || InputTriggerKey(LEFT_TRIGGER) || InputPressKey(A_BUTTON))
		{
			//スクリーンを外に出す
			m_pImage_Screen->SetState(UI_OverScreen::STATE_OVER::STATE_OUT);
			m_NowState = OverState::END;
		}

		if (m_pGameOverInfo->color.w > 1.0f)
		{
			m_pGameOverInfo->color.w = 1.0f;
		}
		else
		{
			if(m_pImage_Screen->GetState() == UI_OverScreen::STATE_OVER::STATE_STAY)
			m_pGameOverInfo->color.w += 1.0f / 120.0f;
		}


		break;
	case OverState::END:
		
		if (m_pGameOverInfo->color.w > 0.0f)
		{
			m_pGameOverInfo->color.w -= 1.0f / 20.0f;
		}
		else
		{
			m_pGameOverInfo->color.w = 0.0f;
		}

		if (m_pImage_Screen->GetState() == UI_OverScreen::STATE_OVER::STATE_END)
		{
			m_NowEXE = true;
		}

		break;
	default:
		break;
	}

	return m_NowEXE;
}

void GameOver::Draw()
{
	//普通に描画
	m_pBackGround->Draw();

	EnableDepth(false);

	//普通に描画
	m_pImage_Screen->ScreenDraw();
	m_pImage_Screen->GameOverDraw();

	for (int i = 0; i < OverSelect::SELECTMAX; i++)
	{
		bool NowSelect = i == m_NowSelect;

		//重ねるように描画
		switch (i)
		{
		case OverSelect::RETRY:
			m_pImage_Screen->RetryDraw(NowSelect);
			break;
		case OverSelect::STAGESELECT:
			m_pImage_Screen->StageSelectDraw(NowSelect);
			break;
		default:
			break;
		}
	}

	if(m_pGameOverInfo != nullptr)
		m_pGameOverInfo->Draw();

	EnableDepth(true);
}

void GameOver::OverInit()
{
	m_NowState = OverState::INIT;

	Stage_Base::GAMEOVER_TYPE nowtype = m_pStage->Get_GameOverType();

	switch (nowtype)
	{
	case Stage_Base::GAMEOVER_DFAULT:
		break;
	case Stage_Base::GAMEOVER_HIT_MAGMA:
		m_pGameOverInfo = new Image2D("Assets/2D/Over/GameOver1.png", m_pSpriteManager);
		break;
	case Stage_Base::GAMEOVER_HIT_SAND:
		m_pGameOverInfo = new Image2D("Assets/2D/Over/GameOver2.png", m_pSpriteManager);
		break;
	case Stage_Base::GAMEOVER_CEILING_DESTROY:
		m_pGameOverInfo = new Image2D("Assets/2D/Over/GameOver3.png", m_pSpriteManager);
		break;
	case Stage_Base::GAMEOVER_JEWELY_DESTROY:
		m_pGameOverInfo = new Image2D("Assets/2D/Over/GameOver4.png", m_pSpriteManager);
		break;
	case Stage_Base::GAMEOVER_JEWELY_MELT:
		m_pGameOverInfo = new Image2D("Assets/2D/Over/GameOver5.png", m_pSpriteManager);
		break;
	case Stage_Base::GAMEOVER_JEWELY_DOROP:
		m_pGameOverInfo = new Image2D("Assets/2D/Over/GameOver6.png", m_pSpriteManager);
		break;
	case Stage_Base::GAMEOVER_MAX:
		break;
	default:
		break;
	}

	m_pGameOverInfo->size = { 1600.0f * 0.35f,250.0f * 0.35f };
	m_pGameOverInfo->pos = { 1280.0f * 0.5f, 720.0f * 0.1f };
	m_pGameOverInfo->color.w = 0.0f;
}
GameOver::OverSelect GameOver::GetEXE()
{
	return m_NowSelect;
}