#include "CameraMain.h"

CameraMain::CameraMain(Stage_Base* stage)
	:m_pStage(stage)
{
	a = { 0.0f,0.0f,0.0f };
	m_b = false;
	m_b2 = false;
	m_b3 = false;
	m_time2 = 99.0f;
	m_totalTime2 = 0.3f;
	AddposX = 0.0f;
	AddposY = 0.0f;
	AddposZ = 0.0f;
	m_AddMove = 0.0f;
	m_time = 0.0f;
	m_totalTime = 0.6f;
	m_pos = { m_pStage->GetPlayer()->GetPos().X + AddposX, m_pStage->GetPlayer()->GetPos().Y + AddposY, m_posZ + AddposZ };
	m_look = { m_pStage->GetPlayer()->GetPos().X + AddposX, m_pStage->GetPlayer()->GetPos().Y + AddposY, m_pStage->GetPlayer()->GetPos().Z };
}

void CameraMain::Update()
{
	if (m_time < m_totalTime)	//カメラ切り替え時の補間用です。returnしたいので特に無ければ上に書いといて下さい。
	{
		CameraMain::Interpolation();
		return;
	}

	if (m_pos.x == m_pStage->GetPlayer()->GetPos().X && m_pos.y == m_pStage->GetPlayer()->GetPos().Y + m_posY && m_pos.z == m_posZ + AddposZ)
	{
		m_b = true;
		m_b2 = false;
	}

	if (IsKeyPress(VK_RIGHT) || IsKeyPress(VK_LEFT) || InputPressKey(LEFT_STICK))
	{
		m_b = false;
		if (m_b2 && !m_b3)
		{
			m_b3 = true;
			m_time2 = 0.0f;
			a = { AddposX,AddposY,AddposZ };
			m_EndPos = { 0.0f,0.0f,0.0f };
		}
	}

	if ((IsKeyPress('A') || IsKeyPress('S') || IsKeyPress('W') || IsKeyPress('D') || InputPressKey(RIGHT_STICK)))
	{
		m_b2 = true;
	}


	DirectX::XMFLOAT2 Addpos = GetPressStick();

	//入力によるカメラの移動処理
	if (IsKeyPress('A') || InputPressKey(RIGHT_STICK))
	{
		if (!(Addpos.x > 0.0f) && (Addpos.x < 0.5f) || IsKeyPress('A'))
		{
			AddposX -= 3.0f;
			m_pos.x += AddposX;
			if (m_pos.x < MinPosX)
			{
				m_pos.x = MinPosX;
				AddposX += 3.0f;
			}
		}
	}
	if (IsKeyPress('D') || InputPressKey(RIGHT_STICK))
	{
		if (!(Addpos.x < 0.0f) && (Addpos.x > 0.5f) || IsKeyPress('D'))
		{
			AddposX += 3.0f;
			m_pos.x += AddposX;
			if (m_pos.x > MaxPosX)
			{
				m_pos.x = MaxPosX;
				AddposX -= 3.0f;
			}
		}
	}
	if (IsKeyPress('W') || InputPressKey(RIGHT_STICK))
	{
		if (!(Addpos.y < 0.0f) && (Addpos.y > 0.5f) || IsKeyPress('W'))
		{
			AddposY += 3.0f;
			m_pos.y += AddposY;
			if (m_pos.y > MaxPosY)
			{
				m_pos.y = MaxPosY;
				AddposY -= 3.0f;
			}
		}
	}
	if (IsKeyPress('S') || InputPressKey(RIGHT_STICK))
	{
		if (!(Addpos.y > 0.0f) && (Addpos.y < 0.5f) || IsKeyPress('S'))
		{
			AddposY -= 3.0f;
			m_pos.y += AddposY;
			if (m_pos.y < MinPosY)
			{
				m_pos.y = MinPosY;
				AddposY += 3.0f;
			}
		}
	}

	if (m_pStage->GetPlayer()->GetJudge() != false)
	{
		if (m_pStage->GetPlayer()->GetRightMove() != false)
		{
			MaxPosX -= 1.5f;
			MinPosX -= 1.5f;
		}
		else
		{
			MaxPosX += 1.5f;
			MinPosX += 1.5f;
		}
	}


	MovePlayerCamera();

	m_pos = { m_pStage->GetPlayer()->GetPos().X + AddposX, m_pStage->GetPlayer()->GetPos().Y + AddposY + m_posY, m_posZ + AddposZ };
	m_look = { m_pStage->GetPlayer()->GetPos().X + AddposX, m_pStage->GetPlayer()->GetPos().Y + AddposY + m_posY, m_pStage->GetPlayer()->GetPos().Z };
}

void CameraMain::ChangeCamera_Init(DirectX::XMFLOAT3 yetPos, DirectX::XMFLOAT3 yetLook)
{
	m_time = 0;
	AddposX = 0;
	AddposY = 0;

	m_EndPos = { m_pStage->GetPlayer()->GetPos().X + AddposX, m_pStage->GetPlayer()->GetPos().Y + AddposY + m_posY, m_posZ + AddposZ };
	m_EndLook = { m_pStage->GetPlayer()->GetPos().X + AddposX, m_pStage->GetPlayer()->GetPos().Y + AddposY + m_posY, m_pStage->GetPlayer()->GetPos().Z };

	if (yetPos.x >= 999.0f && yetLook.z >= 999.0f)
	{
		m_StartPos = m_EndPos;
		m_StartLook = m_EndLook;
	}
	else
	{
		m_StartPos = m_pos = yetPos;
		m_StartLook = m_look = yetLook;
	}
}

void CameraMain::Interpolation()
{
	m_look.x = (m_EndLook.x - m_StartLook.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.x;
	m_look.y = (m_EndLook.y - m_StartLook.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.y;
	m_look.z = (m_EndLook.z - m_StartLook.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartLook.z;

	m_pos.x = (m_EndPos.x - m_StartPos.x) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.x;
	m_pos.y = (m_EndPos.y - m_StartPos.y) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.y;
	m_pos.z = (m_EndPos.z - m_StartPos.z) * sinf((m_time / m_totalTime) * 3.14 / 2) + m_StartPos.z;

	m_time += 1.0f / 60.0f;
}

void CameraMain::MovePlayerCamera()
{
	if (m_time2 < m_totalTime)
	{
		AddposX = (0.0f - a.x) * sinf((m_time2 / m_totalTime) * 3.14 / 2) + a.x;
		AddposY = (0.0f - a.y) * sinf((m_time2 / m_totalTime) * 3.14 / 2) + a.y;
		AddposZ = (0.0f - a.z) * sinf((m_time2 / m_totalTime) * 3.14 / 2) + a.z;

		m_time2 += 1.0f / 60.0f;
	}
	else
	{
		m_b3 = false;
	}

}

