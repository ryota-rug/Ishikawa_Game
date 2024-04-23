//#pragma once
#ifndef OVER_PEOPLE_H
#define OVER_PEOPLE_H

#include <DirectXMath.h>
#include "SpriteManager.h"
#include "BillBoard.h"

class UI_OverPeople
{
public:

public:
	UI_OverPeople(SpriteManager* pSM);
	~UI_OverPeople();
	void Update();
	void Draw();

private:
	BillBoard* m_pPeople[3];
	BillBoard* m_pPeople1[3];
	BillBoard* m_pPeople2[3];
	BillBoard* m_pCar;
	int m_Frame;
};

#endif // OVER_PEOPLE_H