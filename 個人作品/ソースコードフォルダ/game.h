// GameÉVÅ[Éì [game.h]
#pragma once

#include "scene.h"
#include "fieldmanager.h"
#include "enemymanager.h"
#include "explosionmanager.h"

class Game : public Scene
{
private:
	class Transition*	m_Transition{};
	class Audio*		m_BGM{};
	bool m_Goal = false;
	class FieldManager* FieldMan;
	class EnemyManager* EnemyMan;
	class ModelInfo* m_ModelInfo;
	bool m_clear = false;
	bool m_over = false;
public:
	void Init() override;
	void Uninit() override;
	void Update() override;
	FieldManager* GetFieldMan() { return FieldMan; }
	EnemyManager* GetEnemyMan() { return EnemyMan; }
	void Load();
};
