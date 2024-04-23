//#pragma once
#ifndef _H_MAIN_BUNKER_
#define _H_MAIN_BUNKER_
#include "PileBankerBase.h"
#include "Side_Banker.h"
#include "AtkGauge.h"

class Main_Bunker : public PileBanker
{
public:
	Main_Bunker(Stage_Base* MyStage, int LineNum, FloatPos DrawPos, bool Heet);
	~Main_Bunker();
	void Update();
	void Draw();
	void UIDraw() override;
	PileDirection m_GetSideDirection();
	int* Get_pAttack();
	void Can_TypeInSide(bool Can);

private:
	Side_Banker* m_ptempBanker;
	AtkGauge* m_pAtkGauge;
	PileDirection m_Side_Direction;
	DirectX::XMFLOAT2 m_KeyGetPil;
	bool m_SideInstance;
	const int m_Range;
	int m_AddVector;
	bool m_CanCreateSide;
	int m_AnimFrame = 0;
};

#endif // !_H_MAIN_BUNKER_