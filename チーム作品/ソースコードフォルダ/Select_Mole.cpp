#include "Select_Mole.h"
#include <time.h>
//1280,720

Select_Mole::Select_Mole(SpriteManager* pSM)
{
	srand((UINT)time(nullptr));

	for (int i = 0; i < MAX_MOLE; i++)
	{
		m_Mole.push_back({ new Image2D("Assets/2D/animation/mole.png", pSM),0,0,STATE_RAND });
		auto it = m_Mole.end() - 1;
		(*it).m_pMole->pos = { -999.0f,-999.0f };
		(*it).m_pMole->size = { 100,100 };
		(*it).m_pMole->color = { 1.1f,1.1f,1.1f,1.0f };
		(*it).m_pMole->SetTexScale(4, 2);
		(*it).m_pMole->texNum = 1;
	}
}
Select_Mole::~Select_Mole()
{
	for (auto it = m_Mole.begin(); it != m_Mole.end(); it++)
	{
		delete (*it).m_pMole;
	}
	
	m_Mole.clear();
}

void Select_Mole::Update()
{
	for (auto it = m_Mole.begin(); it != m_Mole.end(); it++)
	{
		switch ((*it).m_State)
		{	//Y 620 ～ 700 X 30 ～ 1240
		case STATE_RAND:
			(*it).m_nFrame++;
			if ((*it).m_nFrame++ >= SELECTED_Frame)
			{
				(*it).m_nFrame = 0;

				if (rand() % PRPBABILITY == 1 || (*it).m_nGuaranteeFrame >= PRPBABILITY_GUARANTEE)
				{
					if (rand() % 2 == 1)	//２分の１で反転バージョンになる
					{
						(*it).m_pMole->Reverse(true, false);
					}

					(*it).m_State = STATE_POPUP;
					(*it).m_pMole->pos = { 30.0f + (float)(rand() % 1210),620.0f + (float)(rand() % 80) };
					
					if ((*it).m_pMole->pos.y >= 645)	//プレイヤーより手前か？
					{
						(*it).m_bAround = true;
					}
					else
					{
						(*it).m_bAround = false;
					}
				}
				else
				{
					(*it).m_nGuaranteeFrame++;
				}
			}

			break;

		case STATE_POPUP:
			(*it).m_nFrame++;
			if ((*it).m_nFrame >= ANIME_Frame)
			{
				(*it).m_pMole->texNum += 1;
				(*it).m_nFrame = 0;
			}
			if ((*it).m_pMole->texNum == 3)
			{
				(*it).m_nFrame = 0;
				(*it).m_State = STATE_WAIT;
			}
			break;
			
		case STATE_WAIT:
			(*it).m_nFrame++;
			if ((*it).m_nFrame >= WAIT_FullFrame)
			{
				(*it).m_nFrame = 0;
				(*it).m_State = STATE_MONOLOGUE;
			}
			break;

		case STATE_MONOLOGUE:
			(*it).m_nFrame++;
			if ((*it).m_nFrame >= ANIME_Frame)
			{
				(*it).m_pMole->texNum += 1;
				(*it).m_nFrame = 0;
			}

			if ((*it).m_pMole->texNum == 8)	//アニメの最後まで再生しきったので初期化してまた抽選
			{
				(*it).m_nFrame = 0;
				(*it).m_nGuaranteeFrame = 0;
				(*it).m_State = STATE_RAND;
				(*it).m_pMole->texNum = 0;
				(*it).m_pMole->Reverse(false, false);
				(*it).m_pMole->pos = { 999.0f,999.0f };
			}
			break;
	
		default:
			break;
		}
	}
}

void Select_Mole::BeyondDraw()
{
	for (auto it = m_Mole.begin(); it != m_Mole.end(); it++)
	{
		if (!(*it).m_bAround)
		{
			(*it).m_pMole->Draw();
		}
	}
}

void Select_Mole::FrontDraw()
{
	for (auto it = m_Mole.begin(); it != m_Mole.end(); it++)
	{
		if ((*it).m_bAround)
		{
			(*it).m_pMole->Draw();
		}
	}
}

