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

	// ビヘイビアツリー生成
	behavior.AddNode("", "Root", 0, BehaviorTree::SELECT_RULE::PRIORITY, NULL, NULL);
	behavior.AddNode("Root", "Attack", 2, BehaviorTree::SELECT_RULE::NON, AttackJudgment::GetInstance(), AttackAction::GetInstance());
	behavior.AddNode("Root", "Random", 1, BehaviorTree::SELECT_RULE::NON, NULL, RandomAction::GetInstance());

	// 敵生成
	// 左上
	Enemy* enemy = scene->AddGameObject<Enemy>();
	FieldManager::Info* info = fieldMan->GetInfo(1, 1);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);
	// 右上
	enemy = scene->AddGameObject<Enemy>();
	info = fieldMan->GetInfo(MAX_WIDTH - 2, 1);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);

	// 右下
	enemy = scene->AddGameObject<Enemy>();
	info = fieldMan->GetInfo(MAX_WIDTH - 2, MAX_HEIGHT - 2);
	enemy->SetPosition(info->point);
	enemy->SetNowPosInfo(info);
	enemy->SetAiTree(&behavior);
	m_enemyList.push_back(enemy);

	// 左下
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

	int count = scene->GetGameObject<Score>()->GetCount(); // クリアまでの数

	if (count < 25)
		m_spawn_intarval = 30.0f;

	if (time >= m_spawn_intarval && scene->GetGameObject<Score>()->GetCount() > 0 &&
		m_enemyList.size() <= m_maxEnemy)
	{
		Enemy* enemy = scene->AddGameObject<Enemy>();
		int x = rnd(1, MAX_WIDTH - 2);
		int y = rnd(1, MAX_HEIGHT - 2);

		// 配列内の番号なら
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
// 敵のリスト取得関数
// =================
std::list<Character*> EnemyManager::GetEnemyList()
{
	return m_enemyList;
}

// ===============================
// 指定した敵をリストから削除する関数
// ===============================
void EnemyManager::Erase(Character * enemy)
{
	// NULLになっている敵を取り出す
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
// フィールド内かどうか計算する
// =========================
bool EnemyManager::IsInRange(int x, int y)
{
	if (x >= 1 && x <= MAX_WIDTH - 2 &&
		y >= 1 && y <= MAX_HEIGHT - 2)
	{
		// 範囲内
		return true;
	}
	return false;
}

// ==========================
// ブロックが無い場所を探す関数
// ==========================
void EnemyManager::SetFindEmptySpace(int* x, int* y , FieldManager* field_man)
{
	bool find = false;
	int num = 1;
	while (!find)
	{
		// 左上から順番に見ていく
		for (int j = *y - num; j <= *y + num; j++)
		{
			// 外周だけ探したい
			for (int i = *x - num; i <= *x + num; i++)
			{
				if (j != *y - num && j != *y + num &&
					i != *x - num && i != *x + num)
					continue;

				if (IsInRange(i, j))
				{
					// ブロックがあったら飛ばす
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




