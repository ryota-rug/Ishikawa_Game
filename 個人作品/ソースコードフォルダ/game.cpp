// Gameシーン [game.cpp]
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "audio.h"
#include "modelinfo.h"
#include "camera.h"
#include "sky.h"
#include "field.h"
#include "character.h"
#include "player.h"
#include "enemy.h"
#include "bullet.h"
#include "explosion.h"
#include "box.h"
#include "cylinder.h"
#include "goal.h"
#include "transition.h"
#include "score.h"
#include "game.h"
#include "gameover.h"
#include "clear.h"



void Game::Init()
{
	m_ModelInfo = new ModelInfo();
	Bullet::Load();
	Explosion::Load();
	// カメラ生成
	AddGameObject<Camera>(0);
	// スカイボックス生成
	AddGameObject<Sky>(1);
	// フィールドマネージャー生成
	FieldMan = AddGameObject<GameObject>(1)->AddComponent<FieldManager>();
	// フィールド生成
	AddGameObject<Field>();
	// エネミーマネージャー生成
	EnemyMan = AddGameObject<GameObject>(1)->AddComponent<EnemyManager>();
	// エクスプロージョンマネージャー生成
	AddGameObject<ExplosionManager>();

	// プレイヤー生成
	Player* player = AddGameObject<Player>();
	FieldManager::Info* info = FieldMan->GetInfo(MAX_WIDTH  / 2, MAX_HEIGHT / 2 + 1);
	player->SetPosition(info->point);
	player->SetNowPosInfo(info);

	// スコアUI生成
	AddGameObject<Score>(4);

	m_BGM = AddGameObject<GameObject>(1)->AddComponent<Audio>();
	m_BGM->Load("asset/audio/game.wav");
	m_BGM->Play(true);	// ループ再生

	m_Transition = AddGameObject<Transition>(4);
	m_Transition->FadeIn();
}

void Game::Uninit()
{
	Explosion::Unload();
	Bullet::Unload();
	delete m_ModelInfo;
	m_ModelInfo = nullptr;
}

void Game::Update()
{
	int count = GetGameObject<Score>()->GetCount();
	Player* player = GetGameObject<Player>();

	if (m_Transition->GetState() == Transition::State::Stop)
	{
		if (!m_over && count <= 0)
		{
			m_clear = true;
			Invoke([=]() { m_Transition->FadeOut(); }, 2000);
			m_Transition->FadeOut();
		}
		else if (!m_clear && player == nullptr)
		{
			m_over = true;
			Invoke([=]() { m_Transition->FadeOut(); }, 2000);
			m_Transition->FadeOut();
		}
	}

	if (m_Transition->GetState() == Transition::State::Finish)
	{
		if (m_clear)
		{
			Manager::SetScene<Clear>();
		}
		else if (m_over)
		{
			Manager::SetScene<GameOver>();
		}
	}
}

void Game::Load()
{
	m_ModelInfo->LoadModelInfo("asset/model/Vanguard By T. Choonyung.fbx", "Human");
	m_ModelInfo->LoadAnimInfo("asset/model/Warrior Idle.fbx", "Idle");
	m_ModelInfo->LoadAnimInfo("asset/model/Slow Run.fbx", "Run");
	m_ModelInfo->LoadAnimInfo("asset/model/Jumping.fbx", "Jump");
	
	m_ModelInfo->LoadModelInfo("asset/model/Mutant.fbx", "Enemy");
	m_ModelInfo->LoadAnimInfo("asset/model/Walking.fbx", "Walk");
}
