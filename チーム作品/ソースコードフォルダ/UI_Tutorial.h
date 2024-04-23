//#pragma once
#ifndef UI_TUTORIAL_H
#define UI_TUTORIAL_H

#include <DirectXMath.h>
#include "SpriteManager.h"
#include "Image2D.h"

class UI_Tutorial
{
public:
	UI_Tutorial();
	~UI_Tutorial();
	void Update();
	void Draw();

private:
	SpriteManager* m_pSpriteManager;
	Image2D* m_pXbox;
	Image2D* m_pPC;
	float m_alpha;
	float AlphaCnt;
	bool m_UIFlg;

};

#endif // UI_TUTORIAL_H