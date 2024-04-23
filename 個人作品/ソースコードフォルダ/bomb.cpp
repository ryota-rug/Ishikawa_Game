#include "bomb.h"
#include "modelRenderer.h"
#include "shader.h"
#include "audio.h"
#include "shadow.h"
#include "manager.h"
#include "blockbase.h"
#include "game.h"


void Bomb::Load()
{
	ModelRenderer::Preload("asset/model/bullet.obj");
}

void Bomb::Unload()
{
}

void Bomb::Init()
{
	GameObject::Init();

	AddComponent<Shader>()->Load("shader/vertexLightingVS.cso", "shader/vertexLightingPS.cso");
	AddComponent<ModelRenderer>()->Load("asset/model/bullet.obj");
	AddComponent<Shadow>()->SetSize(1.0f);
	SetScale(DirectX::XMFLOAT3(5.0f, 5.0f, 5.0f));

}

void Bomb::Update()
{
	Explosion();
	//GameObject::Update();

	//if (m_countTime >= m_LifeTime)
	//{
	//	// ����
	//	Explosion();
	//	
	//	
	//}
	//else
	//{
	//	m_countTime += m_deltaTime;
	//}
}

void Bomb::Uninit()
{
}

void Bomb::SetInfo(FieldManager::Info * info)
{
	m_NowPosInfo = info;
	int X = m_NowPosInfo->numX;
	int Y = m_NowPosInfo->numY;

	FieldManager* field_man = static_cast<Game*>(Manager::GetScene())->GetFieldMan();

	// ���ݒn��explosion��true��
	m_NowPosInfo->explosion = true;

	BlockBase* block;
	// �E
	for (int i = 1; i <= m_power; i++)
	{
		block = field_man->GetInfo(X + i, Y)->block;
		if (block != nullptr)
		{
			if (block->GetType() == BlockBase::BlockType::Unbreakable)
				break;

			// ���ʂ̃u���b�N��������1�����󂵂Ă��̐�͔��������Ȃ�
			if (block->GetType() == BlockBase::BlockType::Normal)
			{
				field_man->GetInfo(X + i, Y)->explosion = true;
				break;
			}

			
		}
		field_man->GetInfo(X + i, Y)->explosion = true;
	}
	// ��
	for (int i = -1; i >= -m_power; i--)
	{
		block = field_man->GetInfo(X + i, Y)->block;
		if (block != nullptr)
		{
			if (block->GetType() == BlockBase::BlockType::Unbreakable)
				break;

			// ���ʂ̃u���b�N��������1�����󂵂Ă��̐�͔��������Ȃ�
			if (block->GetType() == BlockBase::BlockType::Normal)
			{
				field_man->GetInfo(X + i, Y)->explosion = true;
				break;
			}
		}
		field_man->GetInfo(X + i, Y)->explosion = true;
	}
	// ��
	for (int j = -1; j >= -m_power; j--)
	{
		block = field_man->GetInfo(X, Y + j)->block;
		if (block != nullptr)
		{
			if (block->GetType() == BlockBase::BlockType::Unbreakable)
				break;

			// ���ʂ̃u���b�N��������1�����󂵂Ă��̐�͔��������Ȃ�
			if (block->GetType() == BlockBase::BlockType::Normal)
			{
				field_man->GetInfo(X, Y + j)->explosion = true;
				break;
			}
		}
		field_man->GetInfo(X, Y + j)->explosion = true;
	}
	// ��
	for (int j = 1; j <= m_power; j++)
	{
		block = field_man->GetInfo(X, Y + j)->block;
		if (block != nullptr)
		{
			if (block->GetType() == BlockBase::BlockType::Unbreakable)
				break;

			// ���ʂ̃u���b�N��������1�����󂵂Ă��̐�͔��������Ȃ�
			if (block->GetType() == BlockBase::BlockType::Normal)
			{
				field_man->GetInfo(X, Y + j)->explosion = true;
				break;
			}
		}
		field_man->GetInfo(X, Y + j)->explosion = true;
	}
}

void Bomb::Explosion()
{
	Manager::GetScene()->GetGameObject<ExplosionManager>()->Generate(m_NowPosInfo);
	SetDestroy();
}
