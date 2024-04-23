#include "character.h"
#include "audio.h"
#include "game.h"
#include "player.h"

void Character::Init()
{
	GameObject::Init();
	m_SE = AddComponent<Audio>();
	m_SE->Load("asset/audio/wan.wav");
}

void Character::Update()
{
	m_OldPos = m_Position;
	m_scene = static_cast<Game*>(Manager::GetScene());
	GameObject::Update();
}

// ==========
// 移動関数
// ==========
bool Character::Move()
{
	switch (m_moveState)
	{
	case MoveState::None:
		
		break;
	case MoveState::Up:
		m_Rotation.y = 0.0f;
		m_Position.z += m_speed * m_deltaTime;
		break;
	case MoveState::Down:
		m_Rotation.y = 180.0f * 3.14f / 180.0f;
		m_Position.z -= m_speed * m_deltaTime;
		break;
	case MoveState::Right:
		m_Rotation.y = 90.0f * 3.14f / 180.0f;
		m_Position.x += m_speed * m_deltaTime;
		break;
	case MoveState::Left:
		m_Rotation.y = 270.0f * 3.14f / 180.0f;
		m_Position.x -= m_speed * m_deltaTime;
		break;
	default:
		break;
	}
		
	return true;
}

// =====================
// ブロックとの当たり判定
// =====================
bool Character::CheckCollisionBlock()
{
	if (m_NowPosInfo == nullptr)
		return false;

	//DirectX::XMFLOAT3 squareSize = m_scene->GetGameObject<FieldManager>()->GetSquareSize();
	DirectX::XMFLOAT3 squareSize = m_scene->GetFieldMan()->GetSquareSize();
	switch (m_moveState)
	{
	case MoveState::None:
		break;
	case MoveState::Up:
		if (m_NowPosInfo->UpInfo->block != nullptr)
		{
			if (m_OldPos.z < m_NowPosInfo->point.z + squareSize.z / 4.0f &&
				m_Position.z > m_NowPosInfo->point.z + squareSize.z / 4.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	case MoveState::Down:
		if (m_NowPosInfo->DownInfo->block != nullptr)
		{
			if (m_OldPos.z  > m_NowPosInfo->point.z - squareSize.z / 4.0f &&
				m_Position.z  < m_NowPosInfo->point.z - squareSize.z / 4.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	case MoveState::Right:
		if (m_NowPosInfo->RightInfo->block != nullptr)
		{
			if (m_OldPos.x < m_NowPosInfo->point.x + squareSize.x / 4.0f &&
				m_Position.x > m_NowPosInfo->point.x + squareSize.x / 4.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	case MoveState::Left:
		if (m_NowPosInfo->LeftInfo->block != nullptr)
		{
			if (m_OldPos.x > m_NowPosInfo->point.x - squareSize.x / 4.0f &&
				m_Position.x  < m_NowPosInfo->point.x - squareSize.x / 4.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	default:
		break;
	}

	return false;
}


bool Character::CheckCollisionBomb()
{
	//DirectX::XMFLOAT3 squareSize = m_scene->GetGameObject<FieldManager>()->GetSquareSize();
	DirectX::XMFLOAT3 squareSize = m_scene->GetFieldMan()->GetSquareSize();
	switch (m_moveState)
	{
	case MoveState::None:
		break;
	case MoveState::Up:
		if (m_NowPosInfo->UpInfo->bomb != nullptr)
		{
			if (m_OldPos.z < m_NowPosInfo->point.z + squareSize.z / 2.0f &&
				m_Position.z > m_NowPosInfo->point.z + squareSize.z / 2.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		
		break;
	case MoveState::Down:
		if (m_NowPosInfo->DownInfo->bomb != nullptr)
		{
			if (m_OldPos.z > m_NowPosInfo->point.z - squareSize.z / 2.0f &&
				m_Position.z < m_NowPosInfo->point.z - squareSize.z / 2.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	case MoveState::Right:
		if (m_NowPosInfo->RightInfo->bomb != nullptr)
		{
			if (m_OldPos.x < m_NowPosInfo->point.x + squareSize.x / 2.0f&&
				m_Position.x > m_NowPosInfo->point.x + squareSize.x / 2.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	case MoveState::Left:
		if (m_NowPosInfo->LeftInfo->bomb != nullptr)
		{
			if (m_OldPos.x > m_NowPosInfo->point.x - squareSize.x / 2.0f &&
				m_Position.x < m_NowPosInfo->point.x - squareSize.x / 2.0f)
			{
				m_Position = m_OldPos;
				return true;
			}
		}
		break;
	default:
		break;
	}

	return false;
}

// ==============================
// マス目分動いたかどうか調べる関数
// ==============================
bool Character::CheckSquareMoved()
{
	DirectX::XMFLOAT3 squareSize = m_scene->GetFieldMan()->GetSquareSize();

	switch (m_moveState)
	{
	case MoveState::Up:
		if (m_Position.z > m_NowPosInfo->point.z + squareSize.z / 2.0f)
		{
			m_NowPosInfo = m_NowPosInfo->UpInfo;
			return true;
		}
		break;
	case MoveState::Down:
		if (m_Position.z < m_NowPosInfo->point.z - squareSize.z / 2.0f)
		{
			m_NowPosInfo = m_NowPosInfo->DownInfo;
			return true;
		}
		break;
	case MoveState::Right:
		if (m_Position.x > m_NowPosInfo->point.x + squareSize.x / 2.0f)
		{
			m_NowPosInfo = m_NowPosInfo->RightInfo;
			return true;
		}
		break;
	case MoveState::Left:
		if (m_Position.x < m_NowPosInfo->point.x - squareSize.x / 2.0f)
		{
			m_NowPosInfo = m_NowPosInfo->LeftInfo;
			return true;
		}
		break;
	}
	return false;
}

// ============================
// Character同士の当たり判定
// ============================
bool Character::CheckCollisionChara()
{
	std::list<Character*> chara_list = m_scene->GetEnemyMan()->GetEnemyList();
	chara_list.push_back(m_scene->GetGameObject<Player>());
	for (auto chara : chara_list)
	{
		if (chara == this)
			continue;

		if (m_Position.x > chara->GetPosition().x - chara->GetScale().x / 2.0f - 1.0f &&
			m_Position.x < chara->GetPosition().x + chara->GetScale().x / 2.0f + 1.0f &&
			m_Position.z < chara->GetPosition().z + chara->GetScale().z / 2.0f + 1.0f &&
			m_Position.z > chara->GetPosition().z - chara->GetScale().z / 2.0f - 1.0f &&
			m_Position.y < chara->GetPosition().y + chara->GetScale().y / 2.0f + 1.0f &&
			m_Position.y > chara->GetPosition().y - chara->GetScale().y / 2.0f - 1.0f)
		{
			return true;
		}
	}



	return false;
}

// =============
// 爆弾設置関数
// =============
void Character::SetBomb()
{
	if (m_NowPosInfo->bomb == nullptr)
	{
		Scene* scene = Manager::GetScene();
		Bomb* bomb = scene->AddGameObject<Bomb>();
		bomb->SetPosition(DirectX::XMFLOAT3(
			m_NowPosInfo->point.x + 0.0f,
			m_NowPosInfo->point.y + 1.0f,
			m_NowPosInfo->point.z + 0.0f));
		m_NowPosInfo->bomb = bomb;
		bomb->SetInfo(m_NowPosInfo);
		m_SE->Play();
	}
}
