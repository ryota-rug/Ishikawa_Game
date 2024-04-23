#include "enemymanager.h"
#include "fieldmanager.h"
#include "manager.h"
//#include "behaviortree.h"
#include "attackjudgment.h"
#include "attackaction.h"
#include "randomaction.h"
#include "game.h"
#include "rand.h"
#include "score.h"

void EnemyManager::Init()
{
	Game* scene = static_cast<Game*>(Manager::GetScene());
	FieldManager* fieldMan = scene->GetFieldMan();

	// �r�w�C�r�A�c���[����
	behavior.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	behavior.AddNode("Root", "Attack", 2, BehaviorTree::SELECT_RULE::NON, AttackJudgment::GetInstance(), AttackAction::GetInstance());
	behavior.AddNode("Root", "Random", 1, BehaviorTree::SELECT_RULE::NON, NULL, RandomAction::GetInstance());

	// �G����
	// ����
	Enemy* enemy = scene->AddGameObject<Enemy>();
	FieldManager::Info* info = fieldMan->GetInfo(1, 1);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);
	// �E��
	enemy = scene->AddGameObject<Enemy>();
	info = fieldMan->GetInfo(MAX_WIDTH - 2, 1);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);

	// �E��
	enemy = scene->AddGameObject<Enemy>();
	info = fieldMan->GetInfo(MAX_WIDTH - 2, MAX_HEIGHT - 2);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);

	// ����
	enemy = scene->AddGameObject<Enemy>();
	info = fieldMan->GetInfo(1, MAX_HEIGHT - 2);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);
}

void EnemyManager::Update()
{
	Game* scene = static_cast<Game*>(Manager::GetScene());
	FieldManager* fieldMan = scene->GetFieldMan();

	int count = scene->GetGameObject<Score>()->GetCount(); // �N���A�܂ł̐�

	if (count < 25)
		m_spawn_intarval = 30.0f;

	if (time >= m_spawn_intarval && scene->GetGameObject<Score>()->GetCount() > 0 &&
		m_enemyList.size() <= m_maxEnemy)
	{
		Enemy* enemy = scene->AddGameObject<Enemy>();
		int x = rnd(1, MAX_WIDTH - 2);
		int y = rnd(1, MAX_HEIGHT - 2);

		// �z����̔ԍ��Ȃ�
		if (IsInRange(x, y))
		{
			if (fieldMan->GetInfo(x, y)->block)
			{
				SetFindEmptySpace(&x, &y, fieldMan);
			}
		}
		FieldManager::Info* info = fieldMan->GetInfo(x , y);
		enemy->SetPosition(DirectX::XMFLOAT3(info->point.x, 10.0f, info->point.z));
		enemy->SetNowPosInfo(info);
		enemy->SetAiTree(&behavior);
		time = 0.0f;
		m_enemyList.push_back(enemy);
	}
	time++;
}

// =================
// �G�̃��X�g�擾�֐�
// =================
std::list<Character*> EnemyManager::GetEnemyList()
{
	return m_enemyList;
}

// ===============================
// �w�肵���G�����X�g����폜����֐�
// ===============================
void EnemyManager::Erase(Character * enemy)
{
	// NULL�ɂȂ��Ă���G�����o��
	for (auto it = m_enemyList.begin(); it != m_enemyList.end(); it++)
	{
		if ((*it) == enemy)
		{
			(*it)->SetDestroy();
			m_enemyList.erase(it);
			break;
		}
	}
}

//==========================
// �t�B�[���h�����ǂ����v�Z����
// =========================
bool EnemyManager::IsInRange(int x, int y)
{
	if (x >= 1 && x <= MAX_WIDTH - 2 &&
		y >= 1 && y <= MAX_HEIGHT - 2)
	{
		// �͈͓�
		return true;
	}
	return false;
}

// ==========================
// �u���b�N�������ꏊ��T���֐�
// ==========================
void EnemyManager::SetFindEmptySpace(int* x, int* y , FieldManager* field_man)
{
	bool find = false;
	int num = 1;
	while (!find)
	{
		// ���ォ�珇�ԂɌ��Ă���
		for (int j = *y - num; j <= *y + num; j++)
		{
			// �O�������T������
			for (int i = *x - num; i <= *x + num; i++)
			{
				if (j != *y - num && j != *y + num &&
					i != *x - num && i != *x + num)
					continue;

				if (IsInRange(i, j))
				{
					// �u���b�N�����������΂�
					if (field_man->GetInfo(i, j)->block)
						continue;

					*x = i;
					*y = j;
					find = true;
				}
			}
		}
		if (num == 5)
			break;
		num++;
	}
	
}




