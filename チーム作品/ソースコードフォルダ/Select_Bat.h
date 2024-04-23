#ifndef __SELECT_BAT_H___
#define __SELECT_BAT_H___

#include "Image2D.h"
#include "SpriteManager.h"

class Select_Bat
{
public:
	Select_Bat(SpriteManager* pSM);
	~Select_Bat();
	void Update();
	void Draw();
	void ResetPos();
private:
	Image2D* m_pBat;	//蝙蝠
	int	m_nFrame;
	int	m_nSinFrame;
	bool m_bEnd = false;	//画面内にいるか
	enum GO
	{
		GO_RIGHT,
		GO_LEFT
	};
	GO m_eGo;
	constexpr static int ANIME_Frame = 2;	//コマ送りにする間隔フレーム
	constexpr static float FLY1_Y = 490;	//飛ぶ高さ1
	constexpr static float FLY2_Y = 30;	//飛ぶ高さ2
	constexpr static float FLY_SPEED_X = 4.6f;	//飛ぶ速さ
};

#endif // !__SELECT_BAT_H___
