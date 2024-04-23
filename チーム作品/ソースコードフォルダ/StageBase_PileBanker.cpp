#include "StageBase.h"
#include <stdio.h>
#include "BlockBase.h"
#include "ItemBase.h"
#include <Windows.h>
#include "PileBankerBase.h"

//ƒpƒCƒ‹ƒoƒ“ƒJ[ 
#include "Main_Bunker.h"
#include "Side_Banker.h"

void Stage_Base::NvigateUpdate()
{
	if (m_pNavigate)
	{
		m_pNavigate->Update();
	}

	if (m_pSideBanker)
	{
		m_pSideBanker->Update();
	}
}

void Stage_Base::NvigateDraw()
{
	//ƒpƒCƒ‹ƒoƒ“ƒJ[•`‰æ
	if (m_pNavigate)
	{
		m_pNavigate->Draw();
	}

	if (m_pSideBanker)
	{
		m_pSideBanker->Draw();
	}
}

//cY‚ğì‚é
void Stage_Base::CreateMainBanker(int LineNum, FloatPos InstancePos, bool Heet)
{
	if (!m_pNavigate)
	{
		Main_Bunker* pMainBanker = new Main_Bunker(this, LineNum, InstancePos, Heet);
		pMainBanker->SetCameraManager(m_pCameraManager);
		pMainBanker->SetModelManager(m_pModelManager);
		pMainBanker->Can_TypeInSide(m_CanTypeIn_Side);
		m_pNavigate = pMainBanker;
	}
}

//‰¡Y‚ğì‚é
void Stage_Base::CreateSideBanker()
{
	//cY‚Íì‚ç‚ê‚Ä‚¢‚é‚¯‚Ç‰¡Y‚Íì‚ç‚ê‚Ä‚¢‚È‚¢ê‡
	if (!m_pSideBanker && m_pNavigate)
	{
		m_pSideBanker = new Side_Banker(this, m_pNavigate);
		m_pSideBanker->SetCameraManager(m_pCameraManager);
		m_pSideBanker->SetModelManager(m_pModelManager);
	}
}

//cY‚ğÁ‚·
void Stage_Base::DestroyMainBanker()
{
	if (m_pNavigate)
	{
		delete m_pNavigate;
		m_pNavigate = nullptr;
	}
}

//‰¡Y‚ğÁ‚·
void Stage_Base::DestroySideBanker()
{
	if (m_pSideBanker)
	{
		delete m_pSideBanker;
		m_pSideBanker = nullptr;
	}
}

//“B‘Å‚¿‚Ìî•ñ‚ğ•Ô‚·
PileBanker* Stage_Base::GetPileBanker()
{
	return m_pNavigate;
}

//‰¡Y‚Ìî•ñ‚ğ•Ô‚·
PileBanker* Stage_Base::GetSideBanker()
{
	return m_pSideBanker;
}

//ƒTƒCƒhƒoƒ“ƒJ[‚ğ‘Å‚¿‚ß‚È‚¢‚æ‚¤‚É‚·‚é
void Stage_Base::SetCantTypeIn_Side()
{
	m_CanTypeIn_Side = false;
}