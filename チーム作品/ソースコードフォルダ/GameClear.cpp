#include "GameClear.h"
#include "Input.h"
#include "XboxKeyboard.h"

GameClear::GameClear(Stage_Base* pStage)
	:m_pStage(pStage)
	,m_pBackGround(nullptr),
	m_NowState(ClearState::STATE_INIT),
	m_NowSelect(ClearSelect::SELECT_NEXT),
	m_NowEXE(false)
{

	m_pSpriteManager = new SpriteManager();

	m_pBackGround = new Image2D{ "Assets/2D/Black.png",m_pSpriteManager };
	m_pBackGround->pos = { 640.0f, 360.0f };
	m_pBackGround->size = { 1280.0f, 720.0f };
	m_pBackGround->angle = { 0.0f, 0.0f, 0.0f };
	m_pBackGround->color = { 1.0f,1.0f,1.0f,0.6f };

	m_pImage_Screen = new UI_ClearScreen();
}

GameClear::~GameClear()
{
	delete m_pBackGround;
	delete m_pImage_Screen;
	delete m_pSpriteManager;
}

bool GameClear::Update()
{
	m_NowEXE = false;

	m_pImage_Screen->Update();

	DirectX::XMFLOAT2 keypos = GetPressStick();

	switch (m_NowState)
	{
	case ClearState::STATE_INIT:
		m_NowSelect = ClearSelect::SELECT_NEXT;
		m_NowState = ClearState::STATE_SELECT;
		m_pImage_Screen->ScreenInit();
		break;
	case ClearState::STATE_SELECT:
		//‰ºƒ{ƒ^ƒ“‚ð‰Ÿ‚·
		if (IsKeyTrigger(VK_DOWN) || InputTriggerKey(DOWN_BUTTON)
			|| (InputPressKey(LEFT_TRIGGER) && keypos.y < 0.0f))
		{
			int SelectNum = m_NowSelect;
			int MaxNum = ClearSelect::SELECT_MAX;
			SelectNum = (SelectNum + 1) % MaxNum;

			m_NowSelect = (ClearSelect)SelectNum;
		}

		//ãƒ{ƒ^ƒ“‚ð‰Ÿ‚·
		if (IsKeyTrigger(VK_UP) || InputTriggerKey(UP_BUTTON)
			|| (InputPressKey(LEFT_TRIGGER) && keypos.y > 0.0f))
		{
			int SelectNum = m_NowSelect;
			int MaxNum = ClearSelect::SELECT_MAX;
			SelectNum = (SelectNum - 1 + MaxNum) % MaxNum;

			m_NowSelect = (ClearSelect)SelectNum;
		}

		if (IsKeyTrigger(VK_RETURN) || InputTriggerKey(LEFT_TRIGGER) || InputPressKey(A_BUTTON))
		{
			m_pImage_Screen->SetState(UI_ClearScreen::STATE_CLEAR::STATE_OUT);
			m_NowState = ClearState::STATE_END;
		}
		break;
	case ClearState::STATE_END:
		if (m_pImage_Screen->GetState() == UI_ClearScreen::STATE_CLEAR::STATE_END)
		{
			m_NowEXE = true;
		}
		break;
	default:
		break;
	}

	return m_NowEXE;
}

void GameClear::Draw()
{
	//•’Ê‚É•`‰æ
	m_pBackGround->Draw();

	EnableDepth(false);

	//•’Ê‚É•`‰æ
	m_pImage_Screen->ScreenDraw();
	m_pImage_Screen->StageClearDraw();
	m_pImage_Screen->UtitukeScoreDraw(m_NockNum);
	m_pImage_Screen->HakaiScoreDraw(m_DestroyBlockNum);
	for (int i = 0; i < GameClear::ClearSelect::SELECT_MAX; i++)
	{
		bool bSelect = m_NowSelect == i;

		//d‚Ë‚é‚æ‚¤‚É•`‰æ
		switch (i)
		{
		case GameClear::ClearSelect::SELECT_RETRY:
			m_pImage_Screen->RetryDraw(bSelect);
			break;
		case GameClear::ClearSelect::SELECT_NEXT:
			m_pImage_Screen->NextDraw(bSelect);
			break;
		case GameClear::ClearSelect::SELECT_STAGESELECT:
			m_pImage_Screen->StageSelectDraw(bSelect);
			break;
		default:
			break;
		}
	}

	EnableDepth(true);

}

void GameClear::ClearInit()
{
	m_NowState = ClearState::STATE_INIT;

	m_NockNum = m_pStage->GetPlayer()->GetKnock()->GetKnockCnt();
	m_DestroyBlockNum = m_pStage->GetBreakInfo()->GetBreckCnt();
}
GameClear::ClearSelect GameClear::GetEXE()
{
	return m_NowSelect;
}