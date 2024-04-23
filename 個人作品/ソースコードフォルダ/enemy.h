// Enemyオブジェクト [enemy.h]
#pragma once

#include "gameObject.h"
#include "character.h"
#include "astarnodemanager.h"


class Enemy : public Character
{
	enum State
	{
		Stopping,
		Moving,
	};
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	void Run();
	void SetAiTree(class BehaviorTree *ai_tree);
	bool MoveToPlayer(); // プレイヤーへ向かう
	bool RandomMove();   // ランダムで動く
	void SetBomb();
	void SearchRoute(FieldManager::Info* goal);
	bool CheckExplosion(); // 現在の場所が爆発範囲内か
	void PreDraw() override;
	int GetDistanceToPlayer(); // プレイヤーとの距離
	bool IsGoal() { return m_bGoal; }
	bool AttackJudg();
private:
	//class AnimationModel* m_Model;
	class BehaviorTree *m_AiTree;			// ビヘイビアツリー
	class BehaviorData *m_BehaviorData;		// ビヘイビアデータ
	class NodeBase *m_ActiveNode;			// 実行中ノード
	class AStarNodeManager* m_AstarMan;		// A*マネージャー
	std::list<FieldManager::Info*> path;	// 経路
	State m_NowState = State::Stopping;
	FieldManager::Info* TargetInfo;			// ターゲットの場所情報
	int m_TargetX; // 向かう先の番号
	int m_TargetY; // 上記と同じ
	int m_MaxMoveMass = 10;		// ランダム時最大何マス動くか
	int m_MoveMass = 0;			// 動いたマスの数
	int m_AnimFrame = 0;
	int m_SightDistance = 7;   // 索敵範囲
	float	m_Blend = 0.0f;
	float m_downspeed = 5.0f;	// 空中から下がるスピード
	float m_lifetime = 0.0f;	// 生成されてからの時間
	float m_attackstarttime = 10.0f; //追いかけ始める秒数 
	bool m_bWalkFlg = false;
	bool m_bJumpFlg = false;
	bool m_bOldWalk = false;
	bool m_bGround = false;		// 地面についているか
	
	bool m_bGoal = false;		// 目的の場所に着いたか

	bool IsWithinTheRange(int x, int y);	// フィールド内かどうか
	void SetHeading();						// 向かう先決定
	void SetRandomHeading();				// ランダムで向かう先決定
	bool CheckArrival();					// 次のポイントに着いたか
};
