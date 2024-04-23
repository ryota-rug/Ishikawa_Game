// Player�I�u�W�F�N�g [player.cpp]
#include "manager.h"
#include "input.h"
#include "shader.h"
#include "animationModel.h"
#include "shadow.h"
#include "audio.h"
#include "game.h"
#include "player.h"
#include "bomb.h"
#include "explosion.h"

void Player::Init()
{
	Character::Init();
	AddComponent<Shader>()->Load("shader/vertexLightingVS.cso", "shader/vertexLightingPS.cso");
	
	m_Model = AddComponent<AnimationModel>();
	m_Model->Load("asset/model/Vanguard By T. Choonyung.fbx", "Human");
	m_Model->LoadAnimation("asset/model/Warrior Idle.fbx", "Idle");
	m_Model->LoadAnimation("asset/model/Slow Run.fbx", "Run");
	m_Model->LoadAnimation("asset/model/Jumping.fbx", "Jump");

	AddComponent<Shadow>()->SetSize(1.5f);


	//m_SE = AddComponent<Audio>();
	//m_SE->Load("asset/audio/wan.wav");

	SetScale(DirectX::XMFLOAT3(0.02f, 0.02f, 0.02f));
	m_bGround = true;
	m_speed = 5.0f * 1.5f;
}


void Player::Update()
{
	Character::Update();

	m_bWalkFlg = false;

	if (Input::GetKeyPress('W') || Input::GetKeyPress('S') || Input::GetKeyPress('D') || Input::GetKeyPress('A'))
	{
		m_bWalkFlg = true;

		// ��ֈړ�
		if (Input::GetKeyPress('W'))
		{
			//m_Rotation.y = 0.0f;
			m_moveState = MoveState::Up;
		}
		// ���ֈړ�
		else if (Input::GetKeyPress('S'))
		{
			//m_Rotation.y = 180.0f * 3.14f / 180.0f;
			m_moveState = MoveState::Down;
		}
		// �E�ֈړ�
		else if (Input::GetKeyPress('D'))
		{
			//m_Rotation.y = 90.0f * 3.14f / 180.0f;
			m_moveState = MoveState::Right;
		}
		// ���ֈړ�
		else if (Input::GetKeyPress('A'))
		{
			//m_Rotation.y = 270.0f * 3.14f / 180.0f;
			m_moveState = MoveState::Left;
		}

		Move();
		CheckColissionBlock();
		CheckSquareMoved();

	}
	else
	{
		m_moveState = MoveState::None;
	}

	// ���e�ݒu
	if (Input::GetKeyTrigger('K'))
	{
		//SetBomb();
	}

	m_AnimFrame++;
}

// �A�j���[�V�����̑J��
void Player::PreDraw()                  
{            
	if (m_bOldWalk != m_bWalkFlg)
	{
		m_Blend = 0.0f;
		m_AnimFrame = 0;
	}

	if (m_bWalkFlg)//���ړ����t���O�ǉ����A�e���Ŏ���.
	{
		m_Model->Update("Idle", m_AnimFrame, "Run", m_AnimFrame, m_Blend);
		m_Blend += 0.1f;
	}
	else
	{
		m_Model->Update("Run", m_AnimFrame, "Idle", m_AnimFrame, m_Blend);//2�ڂ̃A�j���[�V�����𔽉f
		m_Blend += 0.1f;
	}

	if (m_Blend > 1.0f)
	{
		m_Blend = 1.0f;
	}

	m_bOldWalk = m_bWalkFlg;
}

// ====================
// �u���b�N�Ƃ̓����蔻��
// ====================
bool Player::CheckColissionBlock()
{
	std::vector<BlockBase*> block_vector = m_scene->GetGameObjects<BlockBase>();
	for (auto block : block_vector)
	{
		if (m_Position.x > block->GetPosition().x - block->GetScale().x - 0.5f &&
			m_Position.x < block->GetPosition().x + block->GetScale().x + 0.5f &&
			m_Position.z < block->GetPosition().z + block->GetScale().z + 0.5f &&
			m_Position.z > block->GetPosition().z - block->GetScale().z - 0.5f)
		{
			m_Position = m_OldPos;
			return true;
		}
	}
	return false;
}
