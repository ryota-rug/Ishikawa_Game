#pragma once
#include "gameObject.h"
#include <list>
#include "enemy.h"
#include "behaviortree.h"

class EnemyManager : public Component
{
public:
	using Component::Component;
	void Init() override;
	void Update() override;
	std::list<Character*> GetEnemyList();
	void Erase(Character* enemy); // エネミーリストから排除
private:
	std::list<Character*>m_enemyList;
	float time = 0.0f;
	float m_spawn_intarval = 60.0f; // エネミーを生成する間隔
	bool IsInRange(int x, int y); // 範囲チェック
	void SetFindEmptySpace(int* x, int* y , FieldManager* field_man);
	BehaviorTree behavior;
	int m_maxEnemy = 20; // 敵最大数
};

