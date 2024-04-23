#ifndef ___SELECT_STAGE_NUMBER_H___
#define ___SELECT_STAGE_NUMBER_H___

#include "Image2D.h"
#include "SpriteManager.h"

class Select_StageNumber
{
public:
	Select_StageNumber(SpriteManager* pSM);
	~Select_StageNumber();
	void Update();
	void Draw();

private:
	Image2D* m_pLetterStage; //文章「ステージ」
	Image2D* m_pNumber;		 //数字
};


#endif // !___SELECT_STAGE_NUMBER_H___
