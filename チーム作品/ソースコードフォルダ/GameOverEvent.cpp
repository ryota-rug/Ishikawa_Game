#include "GameOverEvent.h"
#include "CameraMiss.h"
#include "Effect_Manager.h"

GameOverEvent::GameOverEvent(Stage_Base* pStage)
	:m_pSceneStage(pStage),
	m_pModelManager(nullptr),
	m_pCameraManager(nullptr),
	m_bEnd(false),
	m_GameOverType(pStage->Get_GameOverType()),
	m_EffectFrame(0)
{
	m_Count = 0;

	m_pHimei = new SE("Assets/SE/GameOver_Voice.wav");

	FloatPos HimeiPos = Stage_Base::CenterPos;
	HimeiPos.Y += m_pSceneStage->GetStageLength().Y * 0.5f;
	
	// ゲームオーバー時に人を出す
	m_pSpriteManager = new SpriteManager;
	m_pImage_Peopre = new UI_OverPeople(m_pSpriteManager);
}

GameOverEvent::~GameOverEvent()
{
	delete m_pSpriteManager;
	delete m_pImage_Peopre;

	delete m_pHimei;
}

void GameOverEvent::Update()
{
	PlayerPos = { m_pSceneStage->GetPlayer()->GetPos().X,m_pSceneStage->GetPlayer()->GetPos().Y,m_pSceneStage->GetPlayer()->GetPos().Z };
	m_GameOverType = m_pSceneStage->Get_GameOverType();
	if (m_Count > 150)
	{
		//この変数をtrueにするとイベントが終わる
		m_bEnd = true;
	}

	switch (m_GameOverType)
	{
	case Stage_Base::GAMEOVER_JEWELY_MELT:
		m_pSceneStage->JewelyUpdate();
		if (m_EffectFrame % 120 == 0)
		{
			DirectX::XMFLOAT3 size = { 25.0f,25.0f,25.0f };
			// プレイヤーの右上に表示したい
			Effect_Manager::Play_Effect("GameOver", { PlayerPos.x + 25.0f,PlayerPos.y + 50.0f,PlayerPos.z }, size);
		}
		m_EffectFrame++;
		break;
	case Stage_Base::GAMEOVER_JEWELY_DOROP:
		if (m_EffectFrame % 120 == 0)
		{
			DirectX::XMFLOAT3 size = { 25.0f,25.0f,25.0f };
			// プレイヤーの右上に表示したい
			Effect_Manager::Play_Effect("GameOver", { PlayerPos.x + 25.0f,PlayerPos.y + 50.0f,PlayerPos.z }, size);
		}
		m_EffectFrame++;
		break;
	case Stage_Base::GAMEOVER_JEWELY_DESTROY:
		m_pSceneStage->JewelyUpdate();
		if (m_EffectFrame % 120 == 0)
		{
			DirectX::XMFLOAT3 size = { 25.0f,25.0f,25.0f };
			// プレイヤーの右上に表示したい
			Effect_Manager::Play_Effect("GameOver", { PlayerPos.x + 25.0f,PlayerPos.y + 50.0f,PlayerPos.z }, size);
		}
		m_EffectFrame++;
		break;
	case Stage_Base::GAMEOVER_HIT_MAGMA:
		if (m_pCameraManager->Get_NowCamera()->GetPos().x == PlayerPos.x)
		{
			if (m_EffectFrame % 120 == 0)
			{
				DirectX::XMFLOAT3 size = { 25.0f,25.0f,25.0f };
				// プレイヤーの右上に表示したい
				Effect_Manager::Play_Effect("GameOver", { PlayerPos.x + 25.0f,PlayerPos.y + 50.0f,PlayerPos.z }, size);
			}
			m_EffectFrame++;
			if (m_EffectFrame >= 120)
				m_bEnd = true;
		}
		break;
	case Stage_Base::GAMEOVER_HIT_SAND:
		if (m_AnimFrame > 60)
		{
			if (m_EffectFrame % 120 == 0)
			{
				DirectX::XMFLOAT3 size = { 25.0f,25.0f,25.0f };
				// プレイヤーの右上に表示したい
				Effect_Manager::Play_Effect("GameOver", { PlayerPos.x + 25.0f,PlayerPos.y + 50.0f,PlayerPos.z }, size);
			}
			m_EffectFrame++;
		}
		if (m_EffectFrame >= 120)
		{
			m_bEnd = true;
			Effect_Manager::GetManager()->StopEffect(m_HimeiHandle);
		}
		break;
	case Stage_Base::GAMEOVER_CEILING_DESTROY:
		break;
	default:
		break;
	}

	m_Count++;
}
void GameOverEvent::Draw()
{
	switch (m_GameOverType)
	{
	case Stage_Base::GAMEOVER_JEWELY_MELT:
		m_pModelManager->c_SetAnimetion("Player", "Over", false);
		m_AnimFrame++;
		break;
	case Stage_Base::GAMEOVER_JEWELY_DOROP:
		m_pModelManager->c_SetAnimetion("Player", "Over", false);
		m_AnimFrame++;
		break;
	case Stage_Base::GAMEOVER_JEWELY_DESTROY:
		m_pModelManager->c_SetAnimetion("Player", "Over", false);
		m_AnimFrame++;
		break;
	case Stage_Base::GAMEOVER_HIT_MAGMA:
		break;
	case Stage_Base::GAMEOVER_HIT_SAND:
		if (m_pCameraManager->Get_NowCamera()->GetPos().x == PlayerPos.x) // カメラがプレイヤーの位置に着いたらアニメーション
		{
			m_pModelManager->c_SetAnimetion("Player", "Over", false);
			m_AnimFrame++;
		}
		break;
	case Stage_Base::GAMEOVER_CEILING_DESTROY:
		m_pImage_Peopre->Draw();	
		break;
	default:
		break;
	}
}
void GameOverEvent::SetStage(Stage_Base* pStage)
{
	m_pSceneStage = pStage;
}
void GameOverEvent::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}
void GameOverEvent::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}
bool GameOverEvent::GetEnd()
{
	return m_bEnd;
}

void GameOverEvent::OverEventInit()
{
	m_GameOverType = m_pSceneStage->Get_GameOverType();

	

	if (m_GameOverType == Stage_Base::GAMEOVER_TYPE::GAMEOVER_CEILING_DESTROY)
	{
		FloatPos HimeiPos = Stage_Base::CenterPos;
		HimeiPos.Y += m_pSceneStage->GetStageLength().Y * 0.5f;
		const float Scale = 50.0f;
		m_HimeiHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("Himei"), HimeiPos.X, HimeiPos.Y, HimeiPos.Z);
		Effect_Manager::GetManager()->SetScale(m_HimeiHandle, Scale, Scale, Scale);
	
		//天井突き抜けたら
		m_pHimei->Play();
	}
}
