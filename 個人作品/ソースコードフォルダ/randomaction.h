#pragma once
#include "actionbase.h"

class Enemy;

class RandomAction : public ActionBase
{
public:
	static RandomAction *GetInstance()
	{
		static RandomAction instance;
		return &instance;
	}

	virtual STATE Run(Enemy *enemy);
};

