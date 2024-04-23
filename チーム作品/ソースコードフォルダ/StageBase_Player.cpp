#include "StageBase.h"
#include <stdio.h>
#include "BlockBase.h"
#include "ItemBase.h"
#include <Windows.h>
#include "PileBankerBase.h"

#include "Player.h"

void Stage_Base::PlayerUpdate()
{
	if (m_pPlayer != nullptr)
	{
		m_pPlayer->Update();
	}
}

void Stage_Base::PlayerDraw()
{
	//ƒvƒŒƒCƒ„[•`‰æ
	if (m_pPlayer)
	{
		m_pPlayer->Draw();
	}
}

void Stage_Base::CreatePlayer()
{
	if (m_pPlayer == nullptr)
	{
		m_pPlayer = new C_Player(this);
	}

	if (m_pJewelryUI != nullptr)
	{
		m_pJewelryUI->SetPlayer(m_pPlayer);
	}
}

void Stage_Base::DeletePlaer()
{
	if (m_pPlayer != nullptr)
	{
		delete m_pPlayer;
		m_pPlayer = nullptr;
	}
}

C_Player* Stage_Base::GetPlayer()
{
	return m_pPlayer;
}