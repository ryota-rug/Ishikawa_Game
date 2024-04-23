#include "GameClearEvent.h"
#include "Effect_Manager.h"

GameClearEvent::GameClearEvent(Stage_Base* pStage)
	:m_pSceneStage(pStage),
	m_pModelManager(nullptr),
	m_pCameraManager(nullptr),
	m_bEnd(false)
{
	m_pEffect = new ClearEffect(m_pSpriteManager);
	m_Count = 0;
}

GameClearEvent::~GameClearEvent()
{
	delete m_pEffect;
}

void GameClearEvent::Update()
{
	m_pEffect->Update();

	if (m_Count > 220)
	{
		Effect_Manager::GetManager()->StopEffect(m_ClearHandle);
		//この変数をtrueにするとイベントが終わる
		m_bEnd = true;
	}

	m_Count++;
}

void GameClearEvent::Draw()
{
	m_pEffect->Draw();
}

void GameClearEvent::ClearEventInit()
{
	m_pModelManager->c_SetAnimetion("Player", "Clear", true);
	DirectX::XMFLOAT3 tempPos;
	tempPos.x = m_pSceneStage->GetPlayer()->GetPos().X;
	tempPos.y = m_pSceneStage->GetPlayer()->GetPos().Y;
	tempPos.z = m_pSceneStage->GetPlayer()->GetPos().Z;
	m_pEffect->Set(tempPos);
	
	m_ClearHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("GameClear"), Effekseer::Vector3D(tempPos.x, tempPos.y, tempPos.z));
	const float Size = 20.0f;
	Effect_Manager::GetManager()->SetScale(m_ClearHandle,Size,Size,Size);
}

void GameClearEvent::SetStage(Stage_Base* pStage)
{
	m_pSceneStage = pStage;	
}

void GameClearEvent::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}

void GameClearEvent::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}

bool GameClearEvent::GetEnd()
{
	return m_bEnd;
}