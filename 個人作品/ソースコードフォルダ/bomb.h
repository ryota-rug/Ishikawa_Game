#pragma once
#include "gameObject.h"
#include "fieldmanager.h"
#include "explosionmanager.h"

class Bomb : public GameObject
{
public:
	static void Load();
	static void Unload();

	void Init() override;
	void Update() override;
	void Uninit() override;
	void SetInfo(FieldManager::Info* info);
	int GetPower() { return m_power; }
	void Explosion();
private:
	int m_power = 2;
	float m_LifeTime = 3.0f; // �����܂ł̎���
	float m_countTime = 0.0f; // �J�E���g�p
	FieldManager::Info* m_NowPosInfo = nullptr;
};

