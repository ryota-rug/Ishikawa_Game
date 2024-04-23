#include "CameraClear.h"

CameraClear::CameraClear(Stage_Base* Stage)
	:m_pStage(Stage)
{
	m_totalTime = 1.0;

}

void CameraClear::Update()
{
	CameraClear::Interpolation();
}

void CameraClear::ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook)
{
	m_time = 0;
	m_StartPos = m_pos = yetPos;
	m_StartLook = m_look = yetLook;

	m_EndPos = { m_pStage->GetPlayer()->GetPos().X , m_pStage->GetPlayer()->GetPos().Y + m_pointY, m_pStage->GetPlayer()->GetPos().Z + m_pointZ };
	m_EndLook = { m_pStage->GetPlayer()->GetPos().X , m_pStage->GetPlayer()->GetPos().Y + m_pointY, m_pStage->GetPlayer()->GetPos().Z};
}

void CameraClear::Interpolation()
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
