#ifndef ___GAME_PAUSE_H___
#define ___GAME_PAUSE_H___

#include "Image2D.h"
#include "SpriteManager.h"
#include "UI_PauseText.h"
#include "UI_PauseScreen.h"


class GamePause
{
public:
	enum PauseState
	{
		INIT = 0,
		SELECT,
		STATEEND,
		STATEMAX
	};

	enum PauseSelect
	{
		RETRY = 0,
		STAGESELECT,
		SELECTEND,
		SELECTMAX,
		SELECTGAMERETURN
	};

public:
	GamePause();
	~GamePause();
	bool Update();
	void Draw();
	void PauseInit();
	PauseSelect GetEXE();


private:
	SpriteManager* m_pSpriteManager;

	Image2D* m_pBackGround;
	PauseState m_NowState;
	PauseSelect m_NowSelect;
	bool m_NowEXE;
	UI_PauseScreen* m_pImage_Screen;
};


#endif // !___GAME_PAUSE_H___
