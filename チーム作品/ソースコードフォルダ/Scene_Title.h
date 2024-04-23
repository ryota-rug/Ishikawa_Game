#ifndef SCENE_TITLE_H
#define SCENE_TITLE_H

#include "Scene.h"
#include "Image2D.h"
#include "Sound.h"

class CScene_Title : public CScene
{
public:
	CScene_Title();
	~CScene_Title();
	void Update();
	void Draw();


private:
	enum SELECT
	{
		SELECT_STAGESELECT = 125,
		SELECT_END = 215
	};

	Image2D* m_pMoveBack[2]; //背景 (動く部分)
	Image2D* m_pBack;		 //背景 (動かない部分)

	Image2D* m_pLogo;	 //タイトルロゴ
	Image2D* m_pSelect;	 //矢印

	Image2D* m_pLetterSelect;		 //文章「ステージセレクト」
	Image2D* m_pLetterOwaru;		 //文章「オワル」
	Image2D* m_pLetterSOUUTITUKE;	 //文章「ソウウチツケスウ」
	Image2D* m_pLetterSOUHAKAI;		 //文章「ソウハカイスウ」

	Image2D* m_pRobo;	//ロボット
	Image2D* m_pNum;	//数字

	BGM* m_pBGM;
	SE* m_pSESelect;
	SE* m_pSEDetermine;

	bool m_determine;
};

#endif // !SCENE_TITLE_H

