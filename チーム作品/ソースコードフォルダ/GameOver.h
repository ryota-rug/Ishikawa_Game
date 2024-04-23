#ifndef ___GAME_OVER_H___
#define ___GAME_OVER_H___

#include "Image2D.h"
#include "SpriteManager.h"
#include "UI_OverScreen.h"
#include "StageBase.h"

class GameOver
{
public:
	enum OverState
	{
		INIT = 0,
		SELECT,
		END,
		STATEMAX
	};

	enum OverSelect
	{
		RETRY = 0,
		STAGESELECT,
		SELECTMAX
	};
public:
	GameOver(Stage_Base* pStage);
	~GameOver();
	bool Update();
	void Draw();
	void OverInit();
	OverSelect GetEXE();

private:
	SpriteManager* m_pSpriteManager;

	Image2D* m_pBackGround;
	OverState m_NowState;
	OverSelect m_NowSelect;
	bool m_NowEXE;
	UI_OverScreen* m_pImage_Screen;
	Image2D* m_pGameOverInfo;
	Stage_Base* m_pStage;
};


#endif // !___GAME_OVER_H___
