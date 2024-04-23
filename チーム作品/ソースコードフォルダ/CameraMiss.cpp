#include "CameraMiss.h"

CameraMiss::CameraMiss(Stage_Base* Stage)
	:m_pStage(Stage)
{
	m_totalTime = 1.0;

	m_pos = { m_pStage->GetPlayer()->GetPos().X,m_pStage->GetPlayer()->GetPos().Y,m_pointZ };//x,y‚ÍplayerÀ•W
	m_look = { m_pStage->GetPlayer()->GetPos().X,m_pStage->GetPlayer()->GetPos().Y,0.0f };

	m_EndLook = { 0,0,0 };
	m_EndPos = { 0,0,1 };
}


void CameraMiss::Update()
{
	m_eType = m_pStage->Get_GameOverType();

	CameraMiss::Interpolation();

	switch (m_eType)
	{
	case Stage_Base::GAMEOVER_DFAULT:
		break;
	case Stage_Base::GAMEOVER_HIT_MAGMA:
		break;
	case Stage_Base::GAMEOVER_HIT_SAND:
		break;
	case Stage_Base::GAMEOVER_CEILING_DESTROY:
		break;
	case Stage_Base::GAMEOVER_JEWELY_DESTROY:
		m_pStage;
		break;;
	default:
		break;
	}
}

void CameraMiss::ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook)
{
	m_time = 0;
	m_StartPos = m_pos = yetPos;
	m_StartLook = m_look = yetLook;

}

void CameraMiss::Set(DirectX::XMFLOAT3 yetPos)
{
	 m_EndLook = yetPos;
	 m_EndPos = { yetPos.x, yetPos .y,yetPos .z + m_pointZ};

}

void CameraMiss::Interpolation()
{
	if (m_time < m_totalTime)
	{
		m_look.x = (m_EndLook.x - m_StartLook.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.x;
		m_look.y = (m_EndLook.y - m_StartLook.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.y;
		m_look.z = (m_EndLook.z - m_StartLook.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.z;

		m_pos.x = (m_EndPos.x - m_StartPos.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.x;
		m_pos.y = (m_EndPos.y - m_StartPos.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.y;
		m_pos.z = (m_EndPos.z - m_StartPos.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.z;

		m_time += 1.0f / 60.0f;
	}
}
