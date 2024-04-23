//#pragma once
#ifndef LOAD_SCREEN_H
#define LOAD_SCREEN_H
#include "Image2D.h"
#include "SpriteManager.h"

class cLoadScreen
{
public:
	enum LOADSCREEN_STATE
	{
		SCREEN_FEEDOUT = 0,	//‰æ–Ê‚ðŠJ‚¯‚é
		SCREEN_DRAW,		//‰æ–Ê‚ð•`‰æ
		SCREEN_FEEDIN		//‰æ–Ê‚ð•Â‚¶‚é
	};

public:
	cLoadScreen();
	~cLoadScreen();
	void Update();
	void Draw();
	LOADSCREEN_STATE GetState();
	bool GetEND();
	void SetLoadEnd(bool End);
	void Init();

private:

	LOADSCREEN_STATE m_State;
	bool m_end;
	SpriteManager* m_pSpriteManager;
	Image2D* m_pBackGround[2];
	Image2D* m_pPlayer;
	Image2D* m_pBlack;
	bool m_LoadEnd;
};

#endif //LOAD_SCREEN_H