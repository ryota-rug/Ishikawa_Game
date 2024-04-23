#include "StartEvent_SideBunker.h"
#include "BlockBase.h"
#include "StartEvent_Player.h"
#include "Effect_Manager.h"

StartEvent_SideBunker::StartEvent_SideBunker(Stage_Base* MyStage, StartEvent_Player* pPlayer)
	: m_pPlayer(pPlayer)
	, m_Range(10)
	,m_pModelManager(nullptr)
	,m_pCameraManager(nullptr)
{
	PileState = PILE_PREPARATION;
	m_pModelManager->c_AddModel("SIDE_PILE", "Assets/New_Character/Kui/yokokui1.fbx");
	m_pModelManager->c_AddModel("SIDE_ADD_PILE", "Assets/New_Character/Kui/addyokokui1.fbx");
	m_pAttackSE = new SE("Assets/SE/Destroy_Block.wav");
	m_SideSize = 0.0f;
	m_BlockPos = pPlayer->GetStageEdge();
	m_BlockPos.Y += Block_Base::BlockSize / 2;
	m_Speed = 3.0f;
	m_BlockPos = m_pPlayer->GetStageEdge();
}

StartEvent_SideBunker::~StartEvent_SideBunker()
{
	delete m_pAttackSE;
}

void StartEvent_SideBunker::Update()
{
	switch (PileState)
	{
	case StartEvent_SideBunker::PILE_PREPARATION:	//準備
	{
		m_DrawPos = m_pPlayer->GetPos();
		m_DrawPos.Y += 40.0f;
		m_DrawPos.X += 2.0f;
		m_InstancePos = m_DrawPos;
		m_StopCount = 0;

		// 右へ打つ
		m_Speed *= 1.0f;

		PileState = StartEvent_SideBunker::PILE_IN;
		break;
	}
	case StartEvent_SideBunker::PILE_IN://パイルが動いている
	{
		//ブロックがあったら
		if (m_BlockPos.X - 25.0f < m_DrawPos.X + m_SideSize)
		{
			m_pPlayer->SetBreakBlockFlg();
			DirectX::XMFLOAT3 Size = { 150.0f,150.0f,150.0f };
			DirectX::XMFLOAT3 Position = { m_BlockPos.X,m_BlockPos.Y + 25,m_BlockPos.Z };
			Effect_Manager::Play_Effect("Clay", Position, Size);
			PileState = StartEvent_SideBunker::PILE_STOP;
		}
		//描画する場所を移動する
		m_DrawPos.X += m_Speed;
		break;
	}

	case StartEvent_SideBunker::PILE_STOP:	//パイルが止まった
	{
		//動かない
		m_StopCount++;

		if (m_StopCount > (int)(60.0f * 0.5f))
		{
			PileState = StartEvent_SideBunker::PILE_BACK;
		}
		m_StopCount;
		break;
	}
	case StartEvent_SideBunker::PILE_BACK://パイルが戻る
	{
		FloatPos BasePos = m_InstancePos;
		m_DrawPos.X -= m_Speed;

		if (BasePos.X < m_DrawPos.X)
		{
			PileState = StartEvent_SideBunker::PILE_DESTROY;
		}
		break;
	}
	case StartEvent_SideBunker::PILE_DESTROY:
		m_Destory = true;
		m_pPlayer->SetState(StartEvent_Player::Event_PlayerState::MOVE);
		break;
	default:
		break;
	}
}

void StartEvent_SideBunker::Draw()
{
	float Angle;
	float Add_Scale = 0.502f;

	Angle = 90.0f;
	Add_Scale *= -1.0f;
	
	m_pModelManager->c_ModelDraw("SIDE_PILE", m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z, 0.3f, 0.3f, 0.3f, 0.0f, Angle, 0.0f);

	switch (PileState)
	{
	case StartEvent_SideBunker::PILE_IN:
		m_SideSize += Add_Scale;
		break;
	case StartEvent_SideBunker::PILE_BACK:
		m_SideSize -= Add_Scale;
		break;
	default:
		break;
	}
	m_pModelManager->c_ModelDraw("SIDE_ADD_PILE", m_DrawPos.X, m_DrawPos.Y, m_DrawPos.Z, 0.3f, 0.3f, m_SideSize, 0.0f, 90.0f, 00.0f);
}

void StartEvent_SideBunker::SetModelManager(CModelManager * pModelManager)
{
	m_pModelManager = pModelManager;
}
void StartEvent_SideBunker::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}
