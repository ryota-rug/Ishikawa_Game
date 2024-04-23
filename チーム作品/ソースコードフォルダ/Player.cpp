#include "Player.h"
#include "StageBase.h"
#include "BlockBase.h"
#include "Input.h"
#include "XboxKeyboard.h"
#include "Main_Bunker.h"
#include "Effect_Manager.h"
#include <math.h>
#include "CameraPile.h"

C_Player::C_Player(Stage_Base* pStage)
	:Stage_Player_Distance(80.0f)
	, m_myStage(pStage)
	, m_NowState(PLAYER_STATE::PLAYER_SELECTNOW)
	, m_Line(0)
	, m_BasePosition({ Stage_Base::CenterPos.X - (Block_Base::BlockSize * (float)m_myStage->GetStageWidthNum().X * 0.5f) + (Block_Base::BlockSize * 0.5f)
	,Stage_Base::CenterPos.Y - ((Block_Base::BlockSize * (float)m_myStage->GetStageWidthNum().Y) * 0.5f) - Stage_Player_Distance
	,Stage_Base::CenterPos.Z })
	,m_Position(m_BasePosition)
	,m_pModelManager(nullptr)
	,m_pCameraManager(nullptr)
	,m_tempBanker(nullptr)
	,m_TotalTime(0.5f)
	,m_movejudge(false)
	,m_moveright(false)
	,m_Rotation(0.0f, -135.0f,0.0f)
	,m_bOnce(false)
	,m_bOnce2(false)
{
	m_pModelManager->c_AddModel("Player", "Assets/New_Character/characterrobonock.fbx");
	m_pModelManager->c_AddAnimetion("Walk", "Assets/New_Character/character_anim_walk.fbx", "Player",25.0f);
	m_pModelManager->c_AddAnimetion("Charge", "Assets/New_Character/character_anim_charge.fbx", "Player",125.0f);
	m_pModelManager->c_AddAnimetion("Charge_First", "Assets/New_Character/character_anim_charge_first.fbx", "Player",100.0f);
	m_pModelManager->c_AddAnimetion("Clear", "Assets/New_Character/character_anim_clear.fbx", "Player",265.0f);
	m_pModelManager->c_AddAnimetion("Over", "Assets/New_Character/character_anim_gameover.fbx", "Player",175.0f);
	m_pModelManager->c_AddAnimetion("knock", "Assets/New_Character/character_anim_knock.fbx", "Player",150.0f);
	m_pModelManager->c_SetAnimetion("Player", "Walk", true);
	m_HeetItemNum = 0;
	m_pHeatGauge = new HeatGauge;
	m_pKnockUI = new KnockUI;

	Effect_Manager::GetManager()->StopEffect(m_SteamHandle);

	m_pWalkSE = new SE("Assets/SE/Caterpillar.wav");
}

C_Player::~C_Player()
{
	delete m_pWalkSE;
	Effect_Manager::GetManager()->StopEffect(m_SteamHandle);
	delete m_pKnockUI;
	delete m_pHeatGauge;
}

void C_Player::Update()
{
	if(!m_bOnce2) 
	{
		m_bOnce2 = true;
		if (m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_STARTEVENT) != nullptr)	//この行も
		{
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN
				, m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_STARTEVENT)->GetPos(),
				m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_STARTEVENT)->GetLook());
		}
		else
		{	//一時的な処理、全てに入場アニメを導入したら消す
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN
				, m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_WORLD)->GetPos(),
				m_pCameraManager->Get_TypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_WORLD)->GetLook());
		}
	}

	m_KeyGet = GetPressStick();
	
	if (IsKeyPress('Q') || InputPressKey(RIGHT_TRIGGER))
	{
		if (!m_bOnce)
		{
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_WORLD
				, m_pCameraManager->Get_NowCamera()->GetPos(),
				m_pCameraManager->Get_NowCamera()->GetLook());
			m_bOnce = true;
		}
	}
	else
	{
		if (m_bOnce)
		{
			m_bOnce = false;

			if (m_myStage->GetPileBanker() != nullptr)
			{
				m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_PILE
					, m_pCameraManager->Get_NowCamera()->GetPos(),
					m_pCameraManager->Get_NowCamera()->GetLook());
			}
			else
			{
				m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN
					, m_pCameraManager->Get_NowCamera()->GetPos(),
					m_pCameraManager->Get_NowCamera()->GetLook());
			}
		}
	}


	switch (C_Player::m_NowState)
	{
	case C_Player::PLAYER_SELECTNOW:
		if (IsKeyPress(VK_RIGHT) || (InputTriggerKey(LEFT_STICK) && (m_KeyGet.x > 0.0f))
			|| (InputPressKey(RIGHT_BUTTON)))//右 
		{
			if (m_myStage->GetStageWidthNum().X - 1 > m_Line)
			{
				// エフェクトの再生
				DirectX::XMFLOAT3 Pos = { m_Position.X + 5.0f , m_Position.Y -10.0f , m_Position.Z };
				DirectX::XMFLOAT3 Size = { 100.0f, 100.0f, 100.0f, };
				DirectX::XMFLOAT3 Rotation = { 0.0f, 180.0f, 0.0f, };
				Effect_Manager::Play_Effect("Move", Pos, Size,Rotation);

				m_NowState = PLAYER_STATE::PLAYER_MOVENOW;
				m_Line++;

				//次のポジションの設定
				m_StartPos = m_Position;
				m_EndPos = {m_BasePosition.X + Block_Base::BlockSize * m_Line,
				m_BasePosition.Y,m_BasePosition.Z};
				m_NowTime = 0.0f;

				m_Rotation.y = -135.0f;
				m_movejudge = true;
				m_pWalkSE->Play();
			}
			m_moveright = true;

			break;
		}

		if (IsKeyPress(VK_LEFT) || (InputTriggerKey(LEFT_STICK) && (m_KeyGet.x < 0.0f))
			|| (InputPressKey(LEFT_BUTTON)))//左 
		{
			if (m_Line > 0)
			{
				// エフェクトの再生
				DirectX::XMFLOAT3 Pos = { m_Position.X - 5.0f , m_Position.Y - 10.0f , m_Position.Z};
				DirectX::XMFLOAT3 Size = {100.0f, 100.0f, 100.0f,};
				Effect_Manager::Play_Effect("Move", Pos, Size);

				m_NowState = PLAYER_STATE::PLAYER_MOVENOW;
				m_Line--;

				//次のポジションの設定
				m_StartPos = m_Position;
				m_EndPos = { m_BasePosition.X + Block_Base::BlockSize * m_Line,
				m_BasePosition.Y,m_BasePosition.Z };
				m_NowTime = 0.0f;

				m_Rotation.y = -45.0f;
				m_movejudge = true;

				m_pWalkSE->Play();
			}
			m_moveright = false;

			break;
		}
		if (IsKeyTrigger(VK_RETURN) || InputTriggerKey(LEFT_TRIGGER) || InputPressKey(A_BUTTON))	//チャージするため一応プレスで
		{
			bool Heet = false;
		

			if (m_HeetItemNum >= 3)
			{
				Heet = true;
				m_HeetItemNum = 0;
				m_pHeatGauge->DecreaseHeat(0.0f);
			}

			m_pModelManager->c_SetAnimetion("Player", "Charge", true);

			//パイルバンカーを作る
			m_myStage->CreateMainBanker(m_Line,m_Position,Heet);
			m_tempBanker = m_myStage->GetPileBanker();
			m_pCameraManager->ChangeTypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_PILE);
			
			m_Rotation.y = -90.0f;
			m_NowState = PLAYER_STATE::PLAYER_SHOTNOW;

			// 打ち付け回数を増やす
			m_pKnockUI->AddKnock(1);
		}

		break;

	case C_Player::PLAYER_MOVENOW:
	{
		//今のポジションを規定の位置まで動かしてやればいい
		//補間をする
		float Persent = m_NowTime / m_TotalTime;

		float Intermediary = Persent < 0.5f ? 2 * pow(Persent, 2) : 1 - pow(-2 * Persent + 2, 3) / 2;

		m_Position.X = (m_EndPos.X - m_StartPos.X) * Intermediary + m_StartPos.X;
		m_Position.Y = (m_EndPos.Y - m_StartPos.Y) * Intermediary + m_StartPos.Y;
		m_Position.Z = (m_EndPos.Z - m_StartPos.Z) * Intermediary + m_StartPos.Z;

		m_NowTime += 1.0f / 60.0f;

		if (m_NowTime > m_TotalTime)
		{
			m_Position = m_EndPos;
			m_NowState = PLAYER_STATE::PLAYER_SELECTNOW;
			m_movejudge = false;
		}

	}
		break;
	case C_Player::PLAYER_SHOTNOW:
		//パイルが動いている間何もしない

		//パイルが壊すときにプレイヤーのステータスを変える
		if(m_tempBanker->GetDestroy())
		{
			if (m_myStage->GetPileBanker()->GetHeet())
			{
				// ヒートゲージ減少
				//m_pHeatGauge->DecreaseHeat(0.0f);
			}
			m_pModelManager->c_SetAnimetion("Player", "Walk", true);
			
			//m_pCameraManager->ChangeTypeCamera(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_DEBUG);
			//if()
			DirectX::XMFLOAT3 temp = {0.0f,0.0f,0.0f};
			m_pCameraManager->ChangeCameraNew(C_CameraManager::SCENE_CAMERA_TYPE::_CAMERA_GAME_MAIN,temp,temp);
			m_myStage->DestroyMainBanker();
			m_NowState = PLAYER_STATE::PLAYER_SELECTNOW;
		}

		break;
	default:
		break;
	}
	
	if (m_HeetItemNum >= 3)
	{
		if (m_EffectFrame % 60 == 0)
		{
			m_SteamHandle = Effect_Manager::GetManager()->Play(Effect_Manager::GetEffect("Steam"), 0.0f, 0.0f, 0.0f);
		}
		Effect_Manager::GetManager()->SetScale(m_SteamHandle, 100.0f, 100.0f, 100.0f);
		Effect_Manager::GetManager()->SetLocation(m_SteamHandle, m_Position.X, m_Position.Y + 10.0f, m_Position.Z);
		m_EffectFrame++;

	}
	else
	{
		m_EffectFrame = 0;
		Effect_Manager::GetManager()->StopEffect(m_SteamHandle);
	}
	

	// ヒートゲージ更新
	m_pHeatGauge->Update();
}

void C_Player::Draw()
{
	m_pModelManager->c_ModelDraw("Player", m_Position.X, m_Position.Y, m_Position.Z, 0.3f, 0.3f, 0.3f
		, m_Rotation.x, m_Rotation.y, m_Rotation.z);
}


// UI表示用
void C_Player::UIDraw()
{
	EnableDepth(false);
	m_pHeatGauge->Draw();
	m_pKnockUI->Draw();
	EnableDepth(true);
}

FloatPos C_Player::GetPos()
{
	return m_Position;
}

void C_Player::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}

void C_Player::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}

void C_Player::MoveOK()
{
	m_NowState = PLAYER_STATE::PLAYER_SELECTNOW;
}

void C_Player::AddHeetItem()
{
	m_HeetItemNum++;

	// ヒートゲージ増加
	m_pHeatGauge->IncreaseHeat(m_HeetItemNum * 30.0f);

	// プレイヤーの現在座標をセット
	m_pHeatGauge->GetPlayerPos(m_Position);

	// カメラの情報をセット
	m_pHeatGauge->GetCameraManager(m_pCameraManager);
}

int C_Player::GetLine()
{
	return m_Line;
}

bool C_Player::GetJudge()
{
	return m_movejudge;
}

bool C_Player::GetRightMove()
{
	return m_moveright;
}

KnockUI* C_Player::GetKnock()
{
	return m_pKnockUI;
}

void C_Player::SetPos(DirectX::XMFLOAT3 SetPos)
{
	m_Position.X = SetPos.x;
	m_Position.Y = SetPos.y;
	m_Position.Z = SetPos.z;
}
