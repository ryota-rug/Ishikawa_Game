#include "Select_Score.h"
#include "Scene_Select.h"
#include "Select_Data.h"



Select_Score::Select_Score(SpriteManager* pSM)
{
	m_pNumber = new Image2D{ "Assets/2D/number_blue.png", pSM };
	m_pNumber->color = { 1.4f, 1.4f, 1.4f, 1.0f };
	m_pNumber->SetTexScale(11, 1);

	m_pLetterUTITUKESUU = new Image2D{ "Assets/2D/select/ウチツケスウ.png", pSM };
	m_pLetterUTITUKESUU->pos.y = 280.0f;
	m_pLetterUTITUKESUU->size = { 170.0f, 30.0f };
	m_pLetterUTITUKESUU->color = { 1.4f, 1.4f, 1.4f, 1.0f };

	m_pLetterBEST = new Image2D{ "Assets/2D/select/ベスト.png", pSM };
	m_pLetterBEST->pos.y = 310.0f;
	m_pLetterBEST->size = { 110.0f, 20.0f };
	m_pLetterBEST->color = { 1.4f, 1.4f, 1.4f, 1.0f };

	m_pLetterHAKAISUU = new Image2D{ "Assets/2D/select/ハカイスウ.png", pSM };
	m_pLetterHAKAISUU->pos.y = 355.0f;
	m_pLetterHAKAISUU->size = { 170.0f, 30.0f };
	m_pLetterHAKAISUU->color = { 1.4f, 1.4f, 1.4f, 1.0f };

	m_pStage = new Image2D{ "Assets/2D/screen.png", pSM };
	m_pStage->pos.y = 285.0f;
	m_pStage->size = { 510.0f, 380.0f };
	m_pStage->color = { 1.0f, 1.5f, 1.5f, 1.0f };


	//セーブデータ取得
	for (int i = 0; i < 15; i++)
	{
		m_data[i] = GetLoadStage(static_cast<SaveElea>(i));

		if (m_data[i].MinHitnum > 99) { m_data[i].MinHitnum = 0; }
		if (m_data[i].AllBlocknum > 999) { m_data[i].AllBlocknum = 999; }
	}
}

Select_Score::~Select_Score()
{
	delete m_pNumber;
	delete m_pLetterUTITUKESUU;
	delete m_pStage;
}

void Select_Score::Update()
{
}

void Select_Score::Draw()
{
	//ステージ情報背景
	m_pStage->pos.x = SELECT1_POS_X; m_pStage->Draw();
	m_pStage->pos.x = SELECT2_POS_X; m_pStage->Draw();
	m_pStage->pos.x = SELECT3_POS_X; m_pStage->Draw();
	m_pStage->pos.x = SELECT4_POS_X; m_pStage->Draw();
	m_pStage->pos.x = SELECT5_POS_X; m_pStage->Draw();


	//ステージ番号
	m_pNumber->pos.y = 215.0f;
	m_pNumber->size = { 60.0f, 60.0f };

	m_pNumber->pos.x = SELECT1_POS_X - 60.0f;	m_pNumber->texNum = SelectState::GetStage();	m_pNumber->Draw();
	m_pNumber->pos.x = SELECT1_POS_X;			m_pNumber->texNum = 10;							m_pNumber->Draw();
	m_pNumber->pos.x = SELECT1_POS_X + 60.0f;	m_pNumber->texNum = 1;							m_pNumber->Draw();
	
	m_pNumber->pos.x = SELECT2_POS_X - 60.0f;	m_pNumber->texNum = SelectState::GetStage();	m_pNumber->Draw();
	m_pNumber->pos.x = SELECT2_POS_X;			m_pNumber->texNum = 10;							m_pNumber->Draw();
	m_pNumber->pos.x = SELECT2_POS_X + 60.0f;	m_pNumber->texNum = 2;							m_pNumber->Draw();
	
	m_pNumber->pos.x = SELECT3_POS_X - 60.0f;	m_pNumber->texNum = SelectState::GetStage();	m_pNumber->Draw();
	m_pNumber->pos.x = SELECT3_POS_X;			m_pNumber->texNum = 10;							m_pNumber->Draw();
	m_pNumber->pos.x = SELECT3_POS_X + 60.0f;	m_pNumber->texNum = 3;							m_pNumber->Draw();

	m_pNumber->pos.x = SELECT4_POS_X - 60.0f;	m_pNumber->texNum = SelectState::GetStage();	m_pNumber->Draw();
	m_pNumber->pos.x = SELECT4_POS_X;			m_pNumber->texNum = 10;							m_pNumber->Draw();
	m_pNumber->pos.x = SELECT4_POS_X + 60.0f;	m_pNumber->texNum = 4;							m_pNumber->Draw();

	m_pNumber->pos.x = SELECT5_POS_X - 60.0f;	m_pNumber->texNum = SelectState::GetStage();	m_pNumber->Draw();
	m_pNumber->pos.x = SELECT5_POS_X;			m_pNumber->texNum = 10;							m_pNumber->Draw();
	m_pNumber->pos.x = SELECT5_POS_X + 60.0f;	m_pNumber->texNum = 5;							m_pNumber->Draw();


	//文章
	m_pLetterUTITUKESUU->pos.x = SELECT1_POS_X; m_pLetterUTITUKESUU->Draw();
	m_pLetterUTITUKESUU->pos.x = SELECT2_POS_X; m_pLetterUTITUKESUU->Draw();
	m_pLetterUTITUKESUU->pos.x = SELECT3_POS_X; m_pLetterUTITUKESUU->Draw();
	m_pLetterUTITUKESUU->pos.x = SELECT4_POS_X; m_pLetterUTITUKESUU->Draw();
	m_pLetterUTITUKESUU->pos.x = SELECT5_POS_X; m_pLetterUTITUKESUU->Draw();

	float tab = 40;
	m_pLetterBEST->pos.x = tab + SELECT1_POS_X; m_pLetterBEST->Draw();
	m_pLetterBEST->pos.x = tab + SELECT2_POS_X; m_pLetterBEST->Draw();
	m_pLetterBEST->pos.x = tab + SELECT3_POS_X; m_pLetterBEST->Draw();
	m_pLetterBEST->pos.x = tab + SELECT4_POS_X; m_pLetterBEST->Draw();
	m_pLetterBEST->pos.x = tab + SELECT5_POS_X; m_pLetterBEST->Draw();

	m_pLetterHAKAISUU->pos.x = SELECT1_POS_X; m_pLetterHAKAISUU->Draw();
	m_pLetterHAKAISUU->pos.x = SELECT2_POS_X; m_pLetterHAKAISUU->Draw();
	m_pLetterHAKAISUU->pos.x = SELECT3_POS_X; m_pLetterHAKAISUU->Draw();
	m_pLetterHAKAISUU->pos.x = SELECT4_POS_X; m_pLetterHAKAISUU->Draw();
	m_pLetterHAKAISUU->pos.x = SELECT5_POS_X; m_pLetterHAKAISUU->Draw();



	//ウチツケスウとハカイスウ
	m_pNumber->size = { 30.0f, 30.0f };
	int space = 30;
	int utitukeRight = 60;
	int hakaiRight = 45;
	UINT nowStageNum = (SelectState::GetStage() - 1) * 5;

	//---ウチツケスウ・ハカイスウの描画
	{
		//ウチツケスウ
		m_pNumber->pos.y = 310.0f;

		m_pNumber->pos.x = SELECT1_POS_X + utitukeRight - space/2;	m_pNumber->texNum = m_data[nowStageNum + 0].MinHitnum / 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT1_POS_X + utitukeRight + space/2;	m_pNumber->texNum = m_data[nowStageNum + 0].MinHitnum % 10;	m_pNumber->Draw();
												   
		m_pNumber->pos.x = SELECT2_POS_X + utitukeRight - space/2;	m_pNumber->texNum = m_data[nowStageNum + 1].MinHitnum / 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT2_POS_X + utitukeRight + space/2;	m_pNumber->texNum = m_data[nowStageNum + 1].MinHitnum % 10;	m_pNumber->Draw();
		
		m_pNumber->pos.x = SELECT3_POS_X + utitukeRight - space/2;	m_pNumber->texNum = m_data[nowStageNum + 2].MinHitnum / 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT3_POS_X + utitukeRight + space/2;	m_pNumber->texNum = m_data[nowStageNum + 2].MinHitnum % 10;	m_pNumber->Draw();

		m_pNumber->pos.x = SELECT4_POS_X + utitukeRight - space/2;	m_pNumber->texNum = m_data[nowStageNum + 3].MinHitnum / 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT4_POS_X + utitukeRight + space/2;	m_pNumber->texNum = m_data[nowStageNum + 3].MinHitnum % 10;	m_pNumber->Draw();

		m_pNumber->pos.x = SELECT5_POS_X + utitukeRight - space/2;	m_pNumber->texNum = m_data[nowStageNum + 4].MinHitnum / 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT5_POS_X + utitukeRight + space/2;	m_pNumber->texNum = m_data[nowStageNum + 4].MinHitnum % 10;	m_pNumber->Draw();


		//ハカイスウ
		m_pNumber->pos.y = 385.0f;

		m_pNumber->pos.x = SELECT1_POS_X + hakaiRight - space;	m_pNumber->texNum = m_data[nowStageNum + 0].AllBlocknum / 100;		m_pNumber->Draw();
		m_pNumber->pos.x = SELECT1_POS_X + hakaiRight;			m_pNumber->texNum = m_data[nowStageNum + 0].AllBlocknum / 10 % 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT1_POS_X + hakaiRight + space;	m_pNumber->texNum = m_data[nowStageNum + 0].AllBlocknum % 10;		m_pNumber->Draw();

		m_pNumber->pos.x = SELECT2_POS_X + hakaiRight - space;	m_pNumber->texNum = m_data[nowStageNum + 1].AllBlocknum / 100;		m_pNumber->Draw();
		m_pNumber->pos.x = SELECT2_POS_X + hakaiRight;			m_pNumber->texNum = m_data[nowStageNum + 1].AllBlocknum / 10 % 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT2_POS_X + hakaiRight + space;	m_pNumber->texNum = m_data[nowStageNum + 1].AllBlocknum % 10;		m_pNumber->Draw();

		m_pNumber->pos.x = SELECT3_POS_X + hakaiRight - space;	m_pNumber->texNum = m_data[nowStageNum + 2].AllBlocknum / 100;		m_pNumber->Draw();
		m_pNumber->pos.x = SELECT3_POS_X + hakaiRight;			m_pNumber->texNum = m_data[nowStageNum + 2].AllBlocknum / 10 % 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT3_POS_X + hakaiRight + space;	m_pNumber->texNum = m_data[nowStageNum + 2].AllBlocknum % 10;		m_pNumber->Draw();

		m_pNumber->pos.x = SELECT4_POS_X + hakaiRight - space;	m_pNumber->texNum = m_data[nowStageNum + 3].AllBlocknum / 100;		m_pNumber->Draw();
		m_pNumber->pos.x = SELECT4_POS_X + hakaiRight;			m_pNumber->texNum = m_data[nowStageNum + 3].AllBlocknum / 10 % 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT4_POS_X + hakaiRight + space;	m_pNumber->texNum = m_data[nowStageNum + 3].AllBlocknum % 10;		m_pNumber->Draw();

		m_pNumber->pos.x = SELECT5_POS_X + hakaiRight - space;	m_pNumber->texNum = m_data[nowStageNum + 4].AllBlocknum / 100;		m_pNumber->Draw();
		m_pNumber->pos.x = SELECT5_POS_X + hakaiRight;			m_pNumber->texNum = m_data[nowStageNum + 4].AllBlocknum / 10 % 10;	m_pNumber->Draw();
		m_pNumber->pos.x = SELECT5_POS_X + hakaiRight + space;	m_pNumber->texNum = m_data[nowStageNum + 4].AllBlocknum % 10;		m_pNumber->Draw();
	}
}
