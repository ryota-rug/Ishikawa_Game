#include "Select_StageNumber.h"
#include "Select_Data.h"


Select_StageNumber::Select_StageNumber(SpriteManager* pSM)
{
	//文章「ステージ」
	m_pLetterStage = new Image2D{ "Assets/2D/select/ステージ.png",pSM };
	m_pLetterStage->pos = { 585.0f, 70.0f };
	m_pLetterStage->size = { 550.0f, 100.0f };
	m_pLetterStage->color = { 1.4f, 1.4f, 1.4f, 1.0f };

	//数字
	m_pNumber = new Image2D{ "Assets/2D/number_blue.png",pSM };
	m_pNumber->pos = { 800.0f, 70.0f };
	m_pNumber->size = { 90.0f, 90.0f };
	m_pNumber->color = { 1.4f, 1.4f, 1.4f, 1.0f };
	m_pNumber->SetTexScale(11, 1);
	m_pNumber->texNum = SelectState::GetStage();
}

Select_StageNumber::~Select_StageNumber()
{
	delete m_pLetterStage;
	delete m_pNumber;
}

void Select_StageNumber::Update()
{
	m_pNumber->texNum = SelectState::GetStage();
}

void Select_StageNumber::Draw()
{
	m_pLetterStage->Draw();
	m_pNumber->Draw();
}
