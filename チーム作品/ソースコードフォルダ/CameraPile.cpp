#include "CameraPile.h"
#include "Input.h"

int g_nFrame;	//許してクレメンス

CameraPile::CameraPile(Stage_Base* Stage)
	:m_pStage(Stage)
{
	m_totalTime = 1.0f;
	m_OldPilePos = { 0,0,0 };
}

void CameraPile::Update()
{
	PileBanker* m_nowPile = m_pStage->GetSideBanker();

	if (!m_nowPile)
	{
		m_nowPile = m_pStage->GetPileBanker();
	}
	else
	{
		int a = 0; a++;
	}



	if (!m_nowPile)
	{
		return;
	}


	m_PileMove.x += m_nowPile->GetDraw().X - m_OldPilePos.x;
	m_PileMove.y += m_nowPile->GetDraw().Y - m_OldPilePos.y;
	m_PileMove.z += m_nowPile->GetDraw().Z - m_OldPilePos.z;

	switch (m_Migrate)
	{
	case CameraInterpolation:
		CameraPile::Interpolation();
		break;

	case CameraPile::MIGRATE_SHOT:
		Shot();
		break;

	case CameraPile::MIGRATE_SIDE:
		Side();
		break;

	default:
		break;
	}

	if (g_nFrame <= m_ShakeFrame)
	{
		Shake();
	}

	m_OldPilePos.x = m_nowPile->GetDraw().X;
	m_OldPilePos.y = m_nowPile->GetDraw().Y;
	m_OldPilePos.z = m_nowPile->GetDraw().Z;
	
	g_nFrame++;
}


void CameraPile::Side()
{
	if (m_pStage->GetSideBanker() == nullptr)
	{
		m_Migrate = CameraPile::MIGRATE_SHOT;
		return;
	}

	m_look = { m_pStage->GetSideBanker()->GetDraw().X,m_pStage->GetSideBanker()->GetDraw().Y + 50.0f,0.0f };
	m_pos = { m_pStage->GetSideBanker()->GetDraw().X,m_pStage->GetSideBanker()->GetDraw().Y + 50.0f,m_pStage->GetSideBanker()->GetDraw().Z + m_pointZ };
	
}

void CameraPile::Shot()
{
	if (m_pStage->GetSideBanker() != nullptr)
	{
		m_Migrate = MIGRATE_SIDE;
		return;
	}
	m_look = { m_pStage->GetPileBanker()->GetDraw().X,m_pStage->GetPileBanker()->GetDraw().Y + 50.0f,0.0f };
	m_pos = { m_pStage->GetPileBanker()->GetDraw().X,m_pStage->GetPileBanker()->GetDraw().Y + 50.0f,m_pStage->GetPileBanker()->GetDraw().Z + m_pointZ };
	
}

void CameraPile::Shake()
{
	m_look.x -= (m_ShakeWidth / 2);
	m_look.y -= (m_ShakeWidth / 2);
	m_look.x += rand() % m_ShakeWidth;
	m_look.y += rand() % m_ShakeWidth;
}

bool CameraPile::GetPile()
{
	if (m_pStage->GetPileBanker() != nullptr)
	{
		return true;
	}

	return false;
}

void CameraPile::ChangeCamera_Init(DirectX::XMFLOAT3 yetPos,DirectX::XMFLOAT3 yetLook)
{
	//パイルの過去座標保存
	if (m_pStage->GetSideBanker() == nullptr)
	{
		m_OldPilePos.x = m_pStage->GetPileBanker()->GetDraw().X;
		m_OldPilePos.y = m_pStage->GetPileBanker()->GetDraw().Y;
		m_OldPilePos.z = m_pStage->GetPileBanker()->GetDraw().Z;
	}
	else
	{
		m_OldPilePos.x = m_pStage->GetSideBanker()->GetDraw().X;
		m_OldPilePos.y = m_pStage->GetSideBanker()->GetDraw().Y;
		m_OldPilePos.z = m_pStage->GetSideBanker()->GetDraw().Z;
	}
	m_PileMove = { 0.0f,0.0f,0.0f };

	m_Migrate = CameraInterpolation;
	g_nFrame = 99;

	if (m_pStage->GetSideBanker() == nullptr)
	{
		m_EndLook = { m_pStage->GetPileBanker()->GetDraw().X,m_pStage->GetPileBanker()->GetDraw().Y + 50.0f, 0.0f };
		m_EndPos = { m_pStage->GetPileBanker()->GetDraw().X,m_pStage->GetPileBanker()->GetDraw().Y + 50.0f,m_pStage->GetPileBanker()->GetDraw().Z + m_pointZ };
	}
	else
	{
		m_EndLook = { m_pStage->GetSideBanker()->GetDraw().X,m_pStage->GetSideBanker()->GetDraw().Y + 50.0f,0.0f };
		m_EndPos = { m_pStage->GetSideBanker()->GetDraw().X,m_pStage->GetSideBanker()->GetDraw().Y + 50.0f,m_pStage->GetSideBanker()->GetDraw().Z + m_pointZ };
	}

	m_time = 0;

	if (yetPos.x >= 999.0f && yetLook.z >= 999.0f)
	{
		m_StartLook = m_look = m_EndLook;
		m_StartPos = m_pos = m_EndPos;
	}
	else
	{
		m_StartLook = m_look = yetLook;
		m_StartPos = m_pos = yetPos;
	}
}

void BiblationCameraPile()
{
	g_nFrame = 0;
}

void CameraPile::Interpolation()
{
	if (m_time < m_totalTime)
	{
		DirectX::XMFLOAT3 tempStartPos = m_StartPos;
		DirectX::XMFLOAT3 tempStartLook = m_StartLook;
		DirectX::XMFLOAT3 tempEndPos = m_EndPos;
		DirectX::XMFLOAT3 tempEndLook = m_EndLook;

		m_StartPos.x += m_PileMove.x;
		m_StartPos.y += m_PileMove.y;
		m_StartPos.z += m_PileMove.z;

		m_StartLook.x += m_PileMove.x;
		m_StartLook.y += m_PileMove.y;
		m_StartLook.z += m_PileMove.z;

		m_EndPos.x += m_PileMove.x;
		m_EndPos.y += m_PileMove.y;
		m_EndPos.z += m_PileMove.z;

		m_EndLook.x += m_PileMove.x;
		m_EndLook.y += m_PileMove.y;
		m_EndLook.z += m_PileMove.z;



		if (m_pStage->GetSideBanker() == nullptr)
		{
			m_look.x = ((m_EndLook.x - m_StartLook.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.x);// +m_PileMove.x;
			m_look.y = ((m_EndLook.y - m_StartLook.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.y);// +m_PileMove.y;
			m_look.z = ((m_EndLook.z - m_StartLook.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.z);// +m_PileMove.z;

			m_pos.x = ((m_EndPos.x - m_StartPos.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.x);// + m_PileMove.x;
			m_pos.y = ((m_EndPos.y - m_StartPos.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.y);// + m_PileMove.y;
			m_pos.z = ((m_EndPos.z - m_StartPos.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.z);// + m_PileMove.z;
		}
		else
		{
			m_look.x = ((m_EndLook.x - m_StartLook.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.x);// + m_PileMove.x;
			m_look.y = ((m_EndLook.y - m_StartLook.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.y);// + m_PileMove.y;
			m_look.z = ((m_EndLook.z - m_StartLook.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.z);// + m_PileMove.z;

			m_pos.x = ((m_EndPos.x - m_StartPos.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.x);// + m_PileMove.x;
			m_pos.y = ((m_EndPos.y - m_StartPos.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.y);// + m_PileMove.y;
			m_pos.z = ((m_EndPos.z - m_StartPos.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.z);// +m_PileMove.z;
		}

		m_StartPos = tempStartPos;
		m_StartLook = tempStartLook;
		m_EndPos = tempEndPos;
		m_EndLook = tempEndLook;


		m_time += 1.0f / 60.0f;
	}
	else
	{
		m_Migrate = CameraPile::MIGRATE_SHOT;
	}
}
