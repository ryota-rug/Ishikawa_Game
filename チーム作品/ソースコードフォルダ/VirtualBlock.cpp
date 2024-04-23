#include "VirtualBlock.h"

VirtualBlock::VirtualBlock(Stage_Base* MyStage, int PosX, int PosY) :
	Block_Base(MyStage, PosX, PosY)
{
	m_Type = BLOCK_INVINCIBLE;
	m_HP = 9999;
	m_DEF = 0;
}

VirtualBlock::~VirtualBlock()
{
}