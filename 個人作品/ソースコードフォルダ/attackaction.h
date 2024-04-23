#pragma once
#include "actionbase.h"

class Enemy;

class AttackAction : public ActionBase
{
public:
	static AttackAction *GetInstance()
	{
		static AttackAction instance;
		return &instance;
	}

	virtual STATE Run(Enemy *enemy);
};

