#ifndef __VIRTUALBLOCK_H__
#define __VIRTUALBLOCK_H__

#include "BlockBase.h"
#include "StageBase.h"

//マップの外側を参照しようとしたときにnullを変えさせない仮想ブロック

class Stage_Base;

class VirtualBlock : public Block_Base
{
public:
	VirtualBlock(Stage_Base* MyStage, int PosX, int PosY);
	~VirtualBlock();

private:

};

#endif // !__VIRTUALBLOCK_H__
