#ifndef ___SELECT_BLOCK_H___
#define ___SELECT_BLOCK_H___

#include "Image2D.h"
#include "SpriteManager.h"
#include "SaveLoad.h"
#include "Game3D.h"
#include "Sound.h"
#include <map>


class Select_Block
{
public:
	Select_Block(SpriteManager* pSM, SCENE beforeScene);
	~Select_Block();
	void Draw();

	bool BreakBlock(); //->bool アニメーション終了フラグ
	bool IsPlayable();

private:
	std::map<SaveElea, Image2D*> m_mapBlocks;
	SaveElea m_breakBlock;
	SE* m_pSEBreak;
};



#endif // !___SELECT_BLOCK_H___
