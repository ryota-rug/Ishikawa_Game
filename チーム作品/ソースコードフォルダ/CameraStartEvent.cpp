#include "CameraStartEvent.h"
#include "DirectX.h"
#include "Position_struct.h"

Camera_StartEvent::Camera_StartEvent(Game_StartEvent* pStartEvent)
	:m_pStartEvent(pStartEvent)
{
	m_pPlayer = pStartEvent->GetPlayer();
	FloatPos TempPos = m_pPlayer->GetPos();

	m_look.x = m_pos.x = TempPos.X;
	m_look.y = m_pos.y = TempPos.Y + 20.0f;
	m_look.z = m_pos.z = TempPos.Z;
	m_pos.z += -150.0f;
}

Camera_StartEvent::~Camera_StartEvent()
{

}

void Camera_StartEvent::Update()
{
	//Œ©‚½‚¢ˆÊ’u
	FloatPos PlayerPos = m_pPlayer->GetPos();
	PlayerPos.Y += 20.0f;
	DirectX::XMFLOAT3 Distance;
	Distance.x = PlayerPos.X - m_pos.x;
	Distance.y = PlayerPos.Y - m_pos.y;

	m_look.x = m_pos.x = Distance.x * 0.08f + m_pos.x;
	m_look.y = m_pos.y = Distance.y * 0.08f + m_pos.y;

}