#pragma once
#include "gameObject.h"
#include "fieldmanager.h"
#include "manager.h"
#include "bomb.h"

class Character : public GameObject
{
public:
	enum MoveState
	{
		None,
		Up,
		Down,
		Right,
		Left,
	};

protected:
	FieldManager::Info* m_NowPosInfo;		// 現在いるマスの情報
	class Game* m_scene;
	DirectX::XMFLOAT3 m_OldPos;
	float m_speed = 5.0f;					// 移動スピード
	MoveState m_moveState = MoveState::None;
	bool Move();
	bool CheckCollisionBlock();
	bool CheckCollisionBomb();
	bool CheckSquareMoved();
	bool CheckCollisionChara();
	bool m_bGround = false;
	class Audio*		m_SE;
	class AnimationModel* m_Model;

public:
	virtual void Init() override;
	virtual void Update() override;
	void SetNowPosInfo(FieldManager::Info* info) { m_NowPosInfo = info; }
	FieldManager::Info* GetOnInfo() { return m_NowPosInfo; }
	void SetBomb();
};