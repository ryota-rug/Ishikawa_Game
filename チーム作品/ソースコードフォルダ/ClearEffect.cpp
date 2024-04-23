#include "ClearEffect.h"

ClearEffect::ClearEffect(SpriteManager* pSM)
{
	m_pMain = new BillBoard("Assets/2D/Clear/Clear_SP.png", pSM);
	m_pMain->pos = { -20.0f,10.0f,10.0f };
	m_pMain->size = { 1000,1000 };
	m_pMain->SetTexScale(4, 4);
	m_pMain->texNum = 0;
	m_nFrame = 0;

	m_bStart = false;
}

ClearEffect::~ClearEffect()
{
	delete m_pMain;
}

void ClearEffect::Update()
{
	if (m_bStart)
	{
		m_nFrame++;

		//画像をコマ送りする
		if (m_nFrame >= ANIME_Frame)
		{
			m_pMain->texNum += 1;
			m_nFrame = 0;
		}

		//リセット
		if (m_pMain->texNum >= 16)
		{
			m_pMain->texNum = 0;
			m_bStart = false;
		}
	}
}

void ClearEffect::Draw()
{
	//m_pMain->Draw();
}

void ClearEffect::Set(DirectX::XMFLOAT3 SetPos)
{
//	m_bStart = true;
//	m_pMain->pos = SetPos;
//	m_pMain->pos = {640.0f,360.0f,0};
}

