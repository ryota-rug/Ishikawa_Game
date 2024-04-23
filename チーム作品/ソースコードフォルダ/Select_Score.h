#ifndef ___SELECT_SCORE_H___
#define ___SELECT_SCORE_H___

#include "Image2D.h"
#include "SpriteManager.h"
#include "SaveLoad.h"

class Select_Score
{
public:
	Select_Score(SpriteManager* pSM);
	~Select_Score();
	void Update();
	void Draw();

private:
	Image2D* m_pStage;	//ステージモニター
	Image2D* m_pLetterUTITUKESUU;	//文章「ウチツケスウ」
	Image2D* m_pLetterBEST;			//文章「ベスト」
	Image2D* m_pLetterHAKAISUU;		//文章「ハカイスウ」
	Image2D* m_pNumber;	//数字

	SaveData m_data[15];
};


#endif // !___SELECT_SCORE_H___
