#include "StartEvent_Player.h"
#include "BlockBase.h"
#include "Player.h"

StartEvent_Player::StartEvent_Player(Stage_Base* pStage)
	:m_pSceneStage(pStage),
	m_pModelManager(nullptr),
	m_pCameraManager(nullptr)
{
	m_pModelManager->c_AddModel("Player", "Assets/New_Character/characterrobonock.fbx");
	m_pModelManager->c_AddAnimetion("Walk", "Assets/New_Character/character_anim_walk.fbx", "Player");
	m_pModelManager->c_AddAnimetion("Charge", "Assets/New_Character/character_anim_charge.fbx", "Player");
	m_pModelManager->c_AddAnimetion("Charge_First", "Assets/New_Character/character_anim_charge_first.fbx", "Player");
	m_pModelManager->c_AddAnimetion("Clear", "Assets/New_Character/character_anim_clear.fbx", "Player");
	m_pModelManager->c_AddAnimetion("Over", "Assets/New_Character/character_anim_gameover.fbx", "Player");
	m_pModelManager->c_AddAnimetion("knock", "Assets/New_Character/character_anim_knock.fbx", "Player");
	m_pModelManager->c_SetAnimetion("Player", "Walk", true);
	m_AnimFlg = false;

	// SE設定
	m_pWalkSE = new SE("Assets/SE/Caterpillar.wav");
	m_pUtuSE = new SE("Assets/SE/Yoko_Uti.wav");

	//ステージのプレイヤーの位置
	m_StagePlayerPos = m_pSceneStage->GetPlayer()->GetPos();

	//ポジションの設定
	IntPos StageWidth = m_pSceneStage->GetStageWidthNum();
	float BlocKSize = Block_Base::BlockSize;
	
	StageEdge.X = Stage_Base::CenterPos.X - (BlocKSize * StageWidth.X * 0.5f) - 100.0f;
	StageEdge.Y = m_StagePlayerPos.Y;
	StageEdge.Z = Stage_Base::CenterPos.Z;
	// 最初のプレイヤーの場所
	m_pos = StageEdge; 
	m_pos.X -= 170.0f;

	//回転量の設定(最初は右向き)
	m_Rotation = { 0.0f, 180.0f, 0.0f};

	//今の動きの設定
	m_NowPlayerState = Event_PlayerState::MOVE;
}


StartEvent_Player::~StartEvent_Player()
{
	delete m_pUtuSE;
	delete m_pWalkSE;
}
void StartEvent_Player::Update()
{
	switch (m_NowPlayerState)
	{
	case Event_PlayerState::MOVE:
	{
		if(m_SEframe % 45 == 0)
			m_pWalkSE->Play();
	
		if (m_AnimFlg)
		{
			m_Rotation.Y = 180.0f;
			m_pModelManager->c_SetAnimetion("Player", "Walk", true);
			m_AnimFlg = false;
		}
		const float Speed = 1.0f;
		//プレイヤーがゲームシーンのプレイヤーのポジションを超えたら
		if (m_StagePlayerPos.X < m_pos.X)
		{
			m_NowPlayerState = Event_PlayerState::END;
		}
		//// プレイヤーがブロックの手前まで来たらチャージアニメーションへ
		if (m_pos.X > StageEdge.X - 75.0f && !m_BreakBlock)
		{
			m_AnimFlg = true;
			m_NowPlayerState = Event_PlayerState::CHARGE;
		}
		m_pos.X += Speed;	// 右へ進む
		m_SEframe++;
	}
		break;
	case Event_PlayerState::END:
		break;
	case Event_PlayerState::MAX:
		break;
	case Event_PlayerState::CHARGE:
		// チャージアニメーション
		if (m_AnimFlg)
		{
			m_Rotation.Y = -90.0f; // 向きをカメラ方向に
			m_pModelManager->c_SetAnimetion("Player", "Charge", true);
			m_AnimFlg = false;
		}
		m_Animframe++;
		 //一定時間経ったらノックアニメ―ションへ切り替え
		if (m_Animframe >= 15)
		{
			m_AnimFlg = true;
			m_NowPlayerState = Event_PlayerState::KNOCK;
			m_Animframe = 0;
		}
		break;
	case Event_PlayerState::KNOCK:
		if (m_AnimFlg)
		{
			m_pUtuSE->Play();
			//m_pModelManager->c_SetAnimetion("Player", "Charge",false);
			m_AnimFlg = false;
		}

		if (m_BreakBlock) // 壊し終わったら歩きアニメーションへ切り替え
		{
			m_AnimFlg = true;
			m_NowPlayerState = Event_PlayerState::MOVE;
		}
		break;
	default:
		break;
	}

}
void StartEvent_Player::Draw()
{
	m_pModelManager->c_ModelDraw("Player", m_pos.X, m_pos.Y, m_pos.Z, 0.3f, 0.3f, 0.3f, m_Rotation.X, m_Rotation.Y, m_Rotation.Z);
}
void StartEvent_Player::SetStage(Stage_Base* pStage)
{
	m_pSceneStage = pStage;
}
void StartEvent_Player::SetModelManager(CModelManager* pModelManager)
{
	m_pModelManager = pModelManager;
}
void StartEvent_Player::SetCameraManager(C_CameraManager* pCameraManager)
{
	m_pCameraManager = pCameraManager;
}

StartEvent_Player::Event_PlayerState StartEvent_Player::GetPlayerState()
{
	return m_NowPlayerState;
}

FloatPos StartEvent_Player::GetPos()
{
	return m_pos;
}