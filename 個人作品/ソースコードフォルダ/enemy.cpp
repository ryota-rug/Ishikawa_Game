// Enemyオブジェクト [enemy.cpp]
#include "enemy.h"
#include "shader.h"
#include "modelRenderer.h"
#include "animationModel.h"
#include "shadow.h"
#include <stdio.h>
#include "BehaviorData.h"
#include "NodeBase.h"
#include "player.h"
#include <vector>
#include "bomb.h"
#include "game.h"
#include "score.h"
#include "rand.h"

void Enemy::Init()
{
	Character::Init();
	AddComponent<Shader>()->Load("shader/vertexLightingVS.cso", "shader/vertexLightingPS.cso");
	m_Model = AddComponent<AnimationModel>();
	m_Model->Load("asset/model/Mutant.fbx", "Enemy");
	m_Model->LoadAnimation("asset/model/Warrior Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset/model/Walking.fbx", "Walk");
	AddComponent<Shadow>()->SetSize(2.0f);


	SetScale(DirectX::XMFLOAT3(0.02f, 0.02f, 0.02f));


	m_speed = static_cast<float>(rnd(m_speed / 2.0f, m_speed));
	m_BehaviorData = new BehaviorData();

	m_AstarMan = new AStarNodeManager();
}

void Enemy::Uninit()
{
	delete m_AstarMan;
	m_AstarMan = nullptr;
}

void Enemy::Update()
{
	m_bWalkFlg = false;
	Character::Update();


	if (m_scene->GetGameObject<Player>() == nullptr)
		return;

	// 着地していない
	if (!m_bGround)
	{
		m_Position.y -= m_downspeed * m_deltaTime;
		if (m_Position.y < 0.0f)
		{
			m_Position.y = 0.0f;
			m_bGround = true;
		}
			
	}
	else
	{
		Run();
	}
	if (CheckCollisionChara())
	{
		SetBomb();
	}
	m_lifetime += m_deltaTime;
	m_AnimFrame++;
}

void Enemy::Run()
{
	if (m_ActiveNode == NULL)
	{
		m_ActiveNode = m_AiTree->Inference(this, m_BehaviorData);
	}

	if (m_ActiveNode != NULL)
	{
		m_ActiveNode = m_AiTree->Run(this, m_ActiveNode, m_BehaviorData);
	}
}



void Enemy::SetAiTree(BehaviorTree * ai_tree)
{
	m_AiTree = ai_tree;
}

bool Enemy::MoveToPlayer()
{
	m_bWalkFlg = true;
	Scene* scene = Manager::GetScene();
	Player* player = scene->GetGameObject<Player>();
	if (player == nullptr)
		return false;

	switch (m_NowState)
	{
	case State::Stopping:
	{
		SearchRoute(player->GetOnInfo());
		if (!path.empty())
		{
			SetHeading();
			m_bGoal = false;
		}
		else
		{
			// 経路が0なら標的と同じ場所にいる
			m_bWalkFlg = false;
			m_bGoal = true;
		}
	}
		break;
	case State::Moving:
	{
		if (path.empty())
		{
			m_moveState = MoveState::None;
			m_NowState = State::Stopping;
			break;
		}

		Move();

		// ブロックに当たらないなら移動可能
		if (!CheckCollisionBlock())
			CheckSquareMoved();

		auto it = path.begin();
		// ポイントに着いたら
		if (m_NowPosInfo->numX == (*it)->numX && m_NowPosInfo->numY == (*it)->numY)
		{
			// ポイントのマスの中まで進んだら
			if (CheckArrival())
			{
				path.erase(it);
				m_moveState = MoveState::None;
				m_NowState = State::Stopping;
				return true;
			}
		}
	}
		break;
	default:
		break;
	}
	return false;
}

bool Enemy::RandomMove()
{
	if (!path.empty())
		path.clear();

	m_bWalkFlg = true;
	switch (m_NowState)
	{
	case State::Stopping:
		SetRandomHeading();
		break;
	case State::Moving:
		Move();

		// ブロックに当たらないなら移動可能
		if (!CheckCollisionBlock())
			CheckSquareMoved();
		else
		{
			m_MoveMass++;
			if (m_MoveMass >= m_MaxMoveMass)
			{
				m_MoveMass = 0;
				m_moveState = MoveState::None;
				m_NowState = State::Stopping;
				break;
			}
		}

		// ポイントのマスの中まで進んだら
		if (CheckArrival())
		{
			m_MoveMass++;
			if (m_MoveMass >= m_MaxMoveMass)
			{
				m_MoveMass = 0;
				m_moveState = MoveState::None;
				m_NowState = State::Stopping;
				break;
			}
			return true;
		}
		break;
	}
	return false;
}

// ============
// 爆弾設置関数
// ============
void Enemy::SetBomb()
{
	if (m_NowPosInfo->bomb == nullptr)
	{
		m_NowPosInfo->bomb = Manager::GetScene()->AddGameObject<Bomb>();
		m_NowPosInfo->bomb->SetPosition(DirectX::XMFLOAT3(m_NowPosInfo->point.x, m_NowPosInfo->point.y + 1.0f, m_NowPosInfo->point.z));
		m_NowPosInfo->bomb->SetInfo(m_NowPosInfo);
	}
}

// =============
// ルート検索関数
// =============
void Enemy::SearchRoute(FieldManager::Info* goal)
{
	path.clear();
	path = m_AstarMan->AStar(m_NowPosInfo, goal);
	path.erase(path.begin()); // 自分のいる場所はいらない
	TargetInfo = goal;
}

// =======================
// いる場所が爆発しているか
// =======================
bool Enemy::CheckExplosion()
{
	if (m_NowPosInfo->explosion)
	{
		return true;
	}
	return false;
}

void Enemy::PreDraw()
{
	if (m_bOldWalk != m_bWalkFlg)
	{
		m_Blend = 0.0f;
		m_AnimFrame = 0;
	}



	if (m_bWalkFlg)//←移動中フラグ追加等、各自で実装.
	{
		m_Model->Update("Idle", m_AnimFrame, "Walk", m_AnimFrame, m_Blend);
		m_Blend += 0.1f;
	}
	else
	{
		m_Model->Update("Walk", m_AnimFrame, "Idle", m_AnimFrame, m_Blend);//2つ目のアニメーションを反映
		m_Blend += 0.1f;
	}

	if (m_Blend > 1.0f)
	{
		m_Blend = 1.0f;
	}

	m_bOldWalk = m_bWalkFlg;
}

// ================================
// プレイヤーとの距離を計算
// ================================
int Enemy::GetDistanceToPlayer()
{
	Player* player = Manager::GetScene()->GetGameObject<Player>();

	if (!player)
		return 100;

	int px, py;
	px = player->GetOnInfo()->numX;
	py = player->GetOnInfo()->numY;

	int ex, ey;
	ex = m_NowPosInfo->numX;
	ey = m_NowPosInfo->numY;

	int numX, numY;
	numX = px - ex;
	if (numX < 0)
		numX *= -1;
	numY = py - ey;
	if (numY < 0)
		numY *= -1;

	return numX + numY;
}

bool Enemy::AttackJudg()
{
	if (GetDistanceToPlayer() <= m_SightDistance || 
		m_lifetime >= m_attackstarttime)
		return true;

	return false;
}

// ===================
// フィールドの範囲内か
// ===================
bool Enemy::IsWithinTheRange(int x, int y)
{
	if (x >= 0 &&
		x < MAX_WIDTH &&
		y >= 0 &&
		y < MAX_HEIGHT)
	{
		return true;
	}

	return false;
}

// ========================
// どの方向に移動するか決める
// ========================
void Enemy::SetHeading()
{
	auto it = path.begin();
	m_TargetX = (*it)->numX;
	m_TargetY = (*it)->numY;
	if (m_NowPosInfo->numY > m_TargetY)
		m_moveState = MoveState::Up;
	if (m_NowPosInfo->numY < m_TargetY)
		m_moveState = MoveState::Down;
	if (m_NowPosInfo->numX < m_TargetX)
		m_moveState = MoveState::Right;
	if (m_NowPosInfo->numX > m_TargetX)
		m_moveState = MoveState::Left;

	if (m_NowPosInfo->numX == m_TargetX &&
		m_NowPosInfo->numY == m_TargetY)
	{
		m_moveState = MoveState::None;
	}


	m_NowState = State::Moving;
}

void Enemy::SetRandomHeading()
{
	m_MoveMass = 0;
	bool find = false;
	int index;
	int moveNum;
	std::list<int> move_list{1, 2, 3, 4};

	for (int i = move_list.size() - 1; i > 0; i--)
	{
		index = rnd(0, i);
		auto it = move_list.begin();
		std::advance(it, index);  // index番目まで移動
		moveNum = *it;			  // 要素格納
		move_list.erase(it);	  // リストから削除

		switch (moveNum)
		{
		case MoveState::Up:
			if (m_NowPosInfo->UpInfo->block == nullptr)
			{
				m_moveState = MoveState::Up;
				find = true;
			}
			break;
		case MoveState::Down:
			if (m_NowPosInfo->DownInfo->block == nullptr)
			{
				m_moveState = MoveState::Down;
				find = true;
			}
			break;
		case MoveState::Right:
			if (m_NowPosInfo->RightInfo->block == nullptr)
			{
				m_moveState = MoveState::Right;
				find = true;
			}
			break;
		case MoveState::Left:
			if (m_NowPosInfo->LeftInfo->block == nullptr)
			{
				m_moveState = MoveState::Left;
				find = true;
			}
			break;
		}
		// 進む先を見つけたら終了
		if (find)
		{
			m_NowState = State::Moving;
			break;
		}
			
	}
}

// ===========================
// 次のポイントに着いたかどうか
// ===========================
bool Enemy::CheckArrival()
{
	float mass_size = static_cast<Game*>(Manager::GetScene())->GetFieldMan()->GetSquareSize().x;
	if (m_Position.x > m_NowPosInfo->point.x - mass_size / 2.0f + 0.5f &&
		m_Position.x < m_NowPosInfo->point.x + mass_size / 2.0f - 0.5f &&
		m_Position.z < m_NowPosInfo->point.z + mass_size / 2.0f - 0.5f &&
		m_Position.z > m_NowPosInfo->point.z - mass_size / 2.0f + 0.5f)
	{
		return true;
	}
	return false;
}
