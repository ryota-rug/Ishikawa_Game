#include "CameraAdmission.h"
#include "BlockBase.h"

CameraAdmission::CameraAdmission(Stage_Base* Stage)
	:m_pStage(Stage)
	,m_start(0.0f, 0.0f, 0.0f), m_end(0.0f, 0.0f, 0.0f)
{	
	LIMIT_LEFT = m_pStage->CenterPos.X - (m_pStage->GetStageWidthNum().X * Block_Base::BlockSize / 2);
	LIMIT_RIGHT = m_pStage->CenterPos.X + m_pStage->GetStageWidthNum().X * Block_Base::BlockSize / 2;
	m_Migrate = MIGRATE_PLAYER;
	m_pos = {m_pStage->GetPlayer()->GetPos().X,m_pStage->GetPlayer()->GetPos().Y,m_pointZ};//x,y��player���W
	m_look = {m_pStage->GetPlayer()->GetPos().X,m_pStage->GetPlayer()->GetPos().Y,0.0f};

}

void CameraAdmission::Update()
{
	switch (m_Migrate)
	{
	case CameraAdmission::MIGRATE_PLAYER:
		Player();
		break;
	default:
		break;
	}

	if (m_pos.x <= LIMIT_LEFT) m_pos.x = LIMIT_LEFT;
	if (m_pos.x >= LIMIT_RIGHT) m_pos.x = LIMIT_RIGHT;
}

void CameraAdmission::Player()
{
	m_look.x = m_pStage->GetPlayer()->GetPos().X;	//�v���C���[��x���W�ɐݒ�
	m_look.y = m_pStage->GetPlayer()->GetPos().Y;

	m_pos.x = m_pStage->GetPlayer()->GetPos().X;	//�v���C���[��x���W�ɐݒ�
	m_pos.y = m_pStage->GetPlayer()->GetPos().Y;
}
