#ifndef __VIRTUALBLOCK_H__
#define __VIRTUALBLOCK_H__

#include "BlockBase.h"
#include "StageBase.h"

//�}�b�v�̊O�����Q�Ƃ��悤�Ƃ����Ƃ���null��ς������Ȃ����z�u���b�N

class Stage_Base;

class VirtualBlock : public Block_Base
{
public:
	VirtualBlock(Stage_Base* MyStage, int PosX, int PosY);
	~VirtualBlock();

private:

};

#endif // !__VIRTUALBLOCK_H__
