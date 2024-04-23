#include "GameStartEvent.h"
#include "BlockBase.h"

Game_StartEvent::Game_StartEvent(Stage_Base* pStage)
	:m_pSceneStage(pStage),
	m_pModelManager(nullptr),
	m_pCameraManager(nullptr),
	m_bEnd(false)
{
	m_pPlayer = new StartEvent_Player(pStage);
	m_pSideBunker = new StartEvent_SideBunker(pStage, m_pPlayer);
	m_BlockDrawPos = m_pPlayer->GetStageEdge();
	m_BlockDrawPos.Y = m_pPlayer->GetStageEdge().Y + 25.0f;
	ADDMODEL_SENDDATA("Soil", "Assets/New_Block/tuti/blocks_tuti.fbx");
}

Game_StartEvent::~Game_StartEvent()
{
	delete m_pSideBunker;
	delete m_pPlayer;
}

void  Game_StartEvent::Update()
{
	m_pPlayer->Update();

	switch (m_pPlayer->GetPlayerState())
	{
	case::StartEvent_Player::Event_PlayerState::MOVE:

		break;
	case::StartEvent_Player::Event_PlayerState::END:
		m_bEnd = true;
		break;
	case::StartEvent_Player::Event_PlayerState::KNOCK:
		m_pSideBunker->Update();
		break;
	case::StartEvent_Player::Event_PlayerState::CHARGE:
		break;
	default:
		break;
	}

}

void Game_StartEvent::Draw()
{
	m_pPlayer->Draw();
	if (m_pPlayer->GetPlayerState() == StartEvent_Player::Event_PlayerState::KNOCK)
	{
		m_pSideBunker->Draw();
	}
	
	if (!m_pPlayer->GetBreakBlockFlg())
	{
		MODELDRAW_SENDDATA("Soil", m_BlockDrawPos, m_blocksize, m_blockangle);
	}
	
}

void Game_StartEvent::SetStage(Stage_Base* pStage)
{
	m_pSceneStage = pStage;
	m_pPlayer->SetStage(pStage);
}

void Game_StartEvent::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
	m_pPlayer->SetModelManager(pModelManager);
	m_pSideBunker->SetModelManager(pModelManager);
}

void Game_StartEvent::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
	m_pPlayer->SetCameraManager(pCameraManager);
	m_pSideBunker->SetCameraManager(pCameraManager);
}

bool Game_StartEvent::GetEnd()
{
	return m_bEnd;
}

StartEvent_Player* Game_StartEvent::GetPlayer()
{
	return m_pPlayer;
}