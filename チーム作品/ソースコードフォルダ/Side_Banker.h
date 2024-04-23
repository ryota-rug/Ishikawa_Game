//#pragma once
#ifndef _H_SIDE_BUNKER_
#define _H_SIDE_BUNKER_
#include "PileBankerBase.h"
#include "ModelManager_Class.h"

class Side_Banker : public PileBanker
{
public :
	Side_Banker(Stage_Base* MyStage,PileBanker* pBanker);
	~Side_Banker();
	void Update();
	void Draw();

private:
	PileBanker* m_pMyBanker;
	int m_AddMap;
	const int m_Range;
	FloatPos m_InstancePos;
	int* m_pMainAttack;
	float m_SideSize;
	float m_CountSpeed;
};


#endif
