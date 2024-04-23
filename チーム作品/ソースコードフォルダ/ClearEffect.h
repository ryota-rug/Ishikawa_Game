#ifndef __CLEAREFFECT_H__
#define __CLEAREFFECT_H__

#include "BillBoard.h"

class ClearEffect
{
public:
	ClearEffect(SpriteManager* pSM);
	~ClearEffect();
	void Update();
	void Draw();
	void Set(DirectX::XMFLOAT3);
private:
	BillBoard* m_pMain;
	int	m_nFrame;
	bool m_bStart;

	constexpr static int ANIME_Frame = 5;	//コマ送りにする間隔フレーム

};





#endif // !__CLEAREFFECT_H__
