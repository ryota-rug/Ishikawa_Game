#include "Select_Bat.h"

Select_Bat::Select_Bat(SpriteManager* pSM)
{
	m_pBat = new Image2D("Assets/2D/animation/bat.png", pSM);
	m_pBat->pos = { -20.0f,FLY1_Y };
	m_pBat->size = { 100,100 };
	m_pBat->color = { 1.5f, 1.5f, 1.5f, 1.0f };
	m_pBat->SetTexScale(7, 1);
	m_nFrame = 0;
	m_pBat->texNum = 0;
	m_bEnd = false;
}

Select_Bat::~Select_Bat()
{
	delete m_pBat;
}

void Select_Bat::Update()
{
	m_nFrame++;
	m_nSinFrame++;

	//画像をコマ送りする
	if (m_nFrame >= ANIME_Frame)
	{
		m_pBat->texNum += 1;
		m_nFrame = 0;
	}
	if (m_pBat->texNum == 6)
	{
		m_pBat->texNum = 0;
		m_nFrame = 0;
	}


	if (!m_bEnd)
	{
		m_bEnd = true;
		m_pBat->pos.y = rand() % 460 + 30;
		
		if (rand() % 2)
		{
			m_pBat->pos.x = 1330.0f;
			m_eGo = GO::GO_LEFT;
			m_pBat->Reverse(false,false);
		}
		else
		{
			m_pBat->pos.x = -50.0f;
			m_eGo = GO::GO_RIGHT;
			m_pBat->Reverse(true, false);
		}
	}

	//ポジションを移動
	switch (m_eGo)
	{
	case Select_Bat::GO_RIGHT:
	m_pBat->pos.x += FLY_SPEED_X;
		break;
	case Select_Bat::GO_LEFT:
	m_pBat->pos.x -= FLY_SPEED_X;
		break;
	default:
		break;
	}

	//画面外に異ったらfm_bEndをfalseに
	if (m_pBat->pos.x > 1330.0f)
	{
		m_bEnd = false;
	}

	if (m_pBat->pos.x < -50.0f)
	{
		m_bEnd = false;
	}

	//縦にゆらゆら
	m_pBat->pos.y += sin(3.14 * m_nSinFrame / 20);

}

void Select_Bat::Draw()
{
	m_pBat->Draw();
}

void Select_Bat::ResetPos()
{
	m_bEnd = false;
}
