#include "PileBankerBase.h"
#include "StageBase.h"
#include "BlockBase.h"
#include "Input.h"
#include "ModelManager.h"

PileBanker::PileBanker(Stage_Base* MyStage)
	:m_MaxAttack(100)
	,PileState(PileBanker::PileSelect::MAX)
	,m_Block_BunkerDistance(100.0f)
	, m_BasePosition({ Stage_Base::CenterPos.X - (Block_Base::BlockSize * (float)MyStage->GetStageWidthNum().X * 0.5f) + (Block_Base::BlockSize * 0.5f)
	,Stage_Base::CenterPos.Y - ((Block_Base::BlockSize * (float)MyStage->GetStageWidthNum().Y) * 0.5f) - m_Block_BunkerDistance
	,Stage_Base::CenterPos.Z })
	,m_ShotSpeed(3.0f)
	,m_PullSpeed(6.0f)
	,m_CountSpeed(0.0f)
	,m_LineNum(0)
	,m_pMyStage(MyStage)
	,m_Destory(false)
	,m_pModelManager(nullptr)
	,m_pCameraManager(nullptr)
	,m_HitStopCount(0)
	,m_PileDrawState(PileBanker::PileDrawTYPE::PILE_DEFAULT)	
{
	m_pAttackSE = new SE("Assets/SE/Destroy_Block.wav");
	m_pStopSE = new SE("Assets/SE/Kui_Stop.wav");
	m_pChageSE = new SE("Assets/SE/Chage.wav");
}
PileBanker::~PileBanker()
{
	delete m_pChageSE;
	delete m_pStopSE;
	delete m_pAttackSE;
}

//打ったときのアップデートなどを入れる
void PileBanker::Update()
{

}

void PileBanker::Draw()
{

}

void PileBanker::UIDraw()
{
}

IntPos PileBanker::GetMap()
{
	return { m_MapPos.X,m_MapPos.Y};
}

FloatPos PileBanker::GetDraw()
{
	return { m_DrawPos.X,m_DrawPos.Y,m_DrawPos.Z };
}

bool PileBanker::GetHeet()
{
	return m_Heet;
}

int PileBanker::GetAttack()
{
	return m_Attack;
}

float PileBanker::GetSpeed()
{
	return m_ShotSpeed;
}

FloatPos PileBanker::GetBasePos()
{
	return m_BasePosition;
}

PileBanker::PileSelect PileBanker::Get_PileState()
{
	return PileState;
}

int PileBanker::Get_Line()
{
	return m_LineNum;
}

bool PileBanker::GetDestroy()
{
	return m_Destory;
}

PileBanker::PileDirection PileBanker::GetDirection()
{
	return 	m_Direction;
}

//モデルマネージャーの登録
void PileBanker::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}

void PileBanker::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}

void PileBanker::StopBanker()
{
	PileState = PileBanker::PileSelect::PILE_STOP;
}