#pragma once
#include "gameObject.h"
#include "fieldmanager.h"

class ExplosionManager : public GameObject
{
public:
	void Init() override;
	void Generate(FieldManager::Info* info);
private:
	class Audio*		m_SE;

};

