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
	Image2D* m_pBat;	//��
	int	m_nFrame;
	int	m_nSinFrame;
	bool m_bEnd = false;	//��ʓ��ɂ��邩
	enum GO
	{
		GO_RIGHT,
		GO_LEFT
	};
	GO m_eGo;
	constexpr static int ANIME_Frame = 2;	//�R�}����ɂ���Ԋu�t���[��
	constexpr static float FLY1_Y = 490;	//��ԍ���1
	constexpr static float FLY2_Y = 30;	//��ԍ���2
	constexpr static float FLY_SPEED_X = 4.6f;	//��ԑ���
};

#endif // !__SELECT_BAT_H___
