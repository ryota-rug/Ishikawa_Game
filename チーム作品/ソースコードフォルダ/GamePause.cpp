#include "GamePause.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "DirectX.h"

GamePause::GamePause()
	:m_pBackGround(nullptr),
	m_NowState(PauseState::INIT),
	m_NowSelect(PauseSelect::RETRY),
	m_NowEXE(false)
{

	m_pSpriteManager = new SpriteManager();
	
	m_pBackGround = new Image2D{ "Assets/2D/Black.png",m_pSpriteManager };
	m_pBackGround->pos   = { 640.0f, 360.0f };
	m_pBackGround->size  = { 1280.0f, 720.0f };
	m_pBackGround->angle = { 0.0f, 0.0f, 0.0f };
	m_pBackGround->color = { 1.0f,1.0f,1.0f,0.6f };


	m_pImage_Screen = new UI_PauseScreen();

}

GamePause::~GamePause()
{
	delete m_pImage_Screen;
	delete m_pBackGround;
	delete m_pSpriteManager;
}

bool GamePause::Update()
{
	DirectX::XMFLOAT2 keypos = GetPressStick();
	m_NowEXE = false;

	m_pImage_Screen->Update();

	switch (m_NowState)
	{
	case PauseState::INIT:
		m_NowSelect = PauseSelect::RETRY;
		m_NowState = PauseState::SELECT;
		m_pImage_Screen->ScreenInit();

		break;
	case PauseState::SELECT:
		//下ボタンを押す
		if (IsKeyTrigger(VK_DOWN) || InputTriggerKey(DOWN_BUTTON)
			|| (InputTriggerKey(LEFT_STICK) && keypos.y < 0.0f))
		{
			int SelectNum = m_NowSelect;
			int MaxNum = PauseSelect::SELECTMAX;
			SelectNum = (SelectNum + 1) % MaxNum;

			m_NowSelect = (PauseSelect)SelectNum;
		}

		//上ボタンを押す
		if (IsKeyTrigger(VK_UP) || InputTriggerKey(UP_BUTTON)
			|| (InputTriggerKey(LEFT_STICK) && keypos.y > 0.0f))
		{
			int SelectNum = m_NowSelect;
			int MaxNum = PauseSelect::SELECTMAX;
			SelectNum = (SelectNum - 1 + MaxNum) % MaxNum;

			m_NowSelect = (PauseSelect)SelectNum;
		}

		if (IsKeyTrigger(VK_RETURN) || InputTriggerKey(LEFT_TRIGGER) || InputTriggerKey(A_BUTTON))
		{
			//スクリーンを外に出す
			m_pImage_Screen->SetState(UI_PauseScreen::STATE_OUT);
			m_NowState = PauseState::STATEEND;
		}

		//ゲームに戻る
		if (IsKeyTrigger(VK_ESCAPE) || InputTriggerKey(BACK_BUTTON) || InputTriggerKey(B_BUTTON))
		{
			//スクリーンを外に出す
			m_pImage_Screen->SetState(UI_PauseScreen::STATE_OUT);
			m_NowSelect = PauseSelect::SELECTGAMERETURN;
			m_NowState = PauseState::STATEEND;
		}
		
		break;
	case PauseState::STATEEND:

		if (m_pImage_Screen->GetState() == UI_PauseScreen::STATE_END)
		{
			m_NowEXE = true;
		}
		break;
	default:
		break;
	}

	return m_NowEXE;
}

void GamePause::Draw()
{

	//普通に描画
	m_pBackGround->Draw();

	EnableDepth(false);

	//普通に描画
	m_pImage_Screen->ScreenDraw();
	m_pImage_Screen->PauseDraw();

	for (int i = 0; i < PauseSelect::SELECTMAX; i++)
	{
		bool bNowSelect = i == m_NowSelect;

		switch (i)
		{
		case PauseSelect::RETRY:
			m_pImage_Screen->RetryDraw(bNowSelect);
			break;
		case PauseSelect::STAGESELECT:
			m_pImage_Screen->StageSelectDraw(bNowSelect);
			break;
		case PauseSelect::SELECTEND:
			m_pImage_Screen->EndDraw(bNowSelect);
			break;
		case PauseSelect::SELECTMAX:
			break;
		default:
			break;
		}
	}
	EnableDepth(true);

}

void GamePause::PauseInit()
{
	m_NowState = PauseState::INIT;
}


GamePause::PauseSelect GamePause::GetEXE()
{
	return m_NowSelect;
}