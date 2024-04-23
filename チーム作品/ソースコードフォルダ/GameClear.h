#ifndef ____GAME_CLEAR_H___
#define ____GAME_CLEAR_H___

#include "Image2D.h"
#include "UI_ClearScreen.h"
#include "StageBase.h"
#include "StageBase.h"

class GameClear
{
public:
	enum ClearState
	{
		STATE_INIT = 0,
		STATE_SELECT,
		STATE_END,
		STATE_MAX
	};

	enum ClearSelect
	{
		SELECT_NEXT = 0,
		SELECT_RETRY,
		SELECT_STAGESELECT,
		SELECT_MAX
	};
public:
	GameClear(Stage_Base* pStage);
	~GameClear();
	bool Update();
	void Draw();
	void ClearInit();
	ClearSelect GetEXE();

private:
	SpriteManager* m_pSpriteManager;

	Stage_Base* m_pStage;
	Image2D* m_pBackGround;
	ClearState m_NowState;
	ClearSelect m_NowSelect;
	bool m_NowEXE;
	UI_ClearScreen* m_pImage_Screen;
	int m_DestroyBlockNum;
	int m_NockNum;
};


#endif // !____GAME_CLEAR_H___
